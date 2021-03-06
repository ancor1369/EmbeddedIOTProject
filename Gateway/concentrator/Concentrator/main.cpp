
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"
#include "Models/Parser.h"

#include <thread>
#include <chrono>
#include <pthread.h>

//Include libraries to deal with the serial port

#include <fcntl.h>
#include <errno.h>
#include <termio.h> //Posix terminal control
#include <unistd.h> //write(), read(), close()

#include <stdio.h>
#include <string.h>

//#include <iostream>
//#include <fstream>
//#include <SerialStream.h>
//#include <stdlib.h>

//These are example messages
#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define message1 "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"02\"}}"

using json = nlohmann::json;
//This object will parse the raw incoming messages
//and will allow me to reuse it as more and more
//messages arrive.
Parser parse;
std::list<MessageRequest> lista;
std::list<MessageRequest>::iterator it;
int serial_port = 0;

//Creating the threads that will make sure the software will
//make its task continuously


void initSerialInterface()
{
	///////Serial interface integration

	//Integration thanks to: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

	//create the serial interface
	serial_port = open("/dev/ttyACM0", O_RDWR);

	struct termios tty;

	if(tcgetattr(serial_port, &tty) != 0)
	{
		std::cout << "Error opening the serial port" << std::endl;
	}

	//Integration of the serial interface

	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag |= CS8; // 8 bits per byte (most common)
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

	tty.c_cc[VTIME] = 1;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 1;

	// Set in/out baud rate to be 115200
	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);

	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
	{
	    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	}
}



/*
 * This thread function reads the information from the
 * serial interface and then pushes the captured data into
 * the list we are using to store the incoming messages
 */
void *readDataFromSerial(void * param)
{

	//https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
	//Receiving algorithm thanks to the above post
	initSerialInterface();
	try
	{

		std::string inputMessage;
		std::string temMessage;
		do {
			char buf[16];
			int rdlen;
			rdlen = read(serial_port, buf, sizeof(buf) - 1);
			if (rdlen > 0) {
				buf[rdlen] = 0;
				//printf("Read %d: \"%s\"\n", rdlen, buf);

				if(buf[0] != 0x00)
				{
					inputMessage += std::string(buf);
				}
				else
				{
					if(inputMessage != "")
					{
						//Finally here I can get the full message as required to be processed
						std::cout << inputMessage << std::endl;
						//Push the message to be processed
						parse.setRawMessage(inputMessage);
						lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));
					}
					inputMessage = "";
				}

			} else if (rdlen < 0) {
				printf("Error from read: %d: %s\n", rdlen, strerror(errno));
			} else {  /* rdlen == 0 */
				printf("Timeout from read\n");
			}
			/* repeat read to get full message */
		} while (1);
	}catch (const std::exception &e) {
		std::cout << e.what()<<std::endl;
	}

	close(serial_port);


}

/*
 * This thread takes the information in the
 * list, makes the requests and finally, if the
 * request has a response, it will remove it from
 * the list and then leaves everything ready to
 * continue to process the incoming information
 */
void *processData(void * param)
{

	std::string response;


	while(1)
	{
		it = lista.begin();
		while(it != lista.end())
		{
			it->sendRequest();
			if(it->getResponse() != "")
			{
				response = it->getSender()+it->getResponse() + "\r";
				std::cout<<response<<std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				write(serial_port,response.c_str(),response.size());

				lista.erase(it++);
			}
			else
			{
				++it;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

/*
 * This is the main code of the application where I start
 * the threads that will make sure the application will be running.
 */
int main()
{
	pthread_t rThread;
	pthread_t sThread;

	if(pthread_create(&rThread,NULL,readDataFromSerial,NULL))
	{
		std::cout<<"Error creating thread, Ending program!"<<std::endl;
		return 1;
	}

	if(pthread_create(&sThread,NULL,processData,NULL))
	{
		std::cout<<"Error creating thread, Ending program!"<<std::endl;
		return 1;
	}

	//Run for ever to keep the application alive
	//In a real time operative system, this would be replaced
	//by scheduler taking care of the tasks going on
	while(1)
	{
		std::cout<<"tick"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
