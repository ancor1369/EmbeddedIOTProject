
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"
#include "Models/Parser.h"

#include <thread>
#include <chrono>
#include <pthread.h>

#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define message1 "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"02\"}}"

using json = nlohmann::json;
//This object will parse the raw incoming messages
//and will allow me to reuse it as more and more
//messages arrive.
Parser parse;
std::list<MessageRequest> lista;
std::list<MessageRequest>::iterator it;

//Creating the threads that will make sure the software will
//make its task continuously

/*
 * This thread function reads the information from the
 * serial interface and then pushes the captured data into
 * the list we are using to store the incoming messages
 */
void *readDataFromSerial(void * param)
{

	std::string inputMessage;
	while(1)
	{
		try
		{
			std::cin>>inputMessage;
			parse.setRawMessage(inputMessage);
			lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		catch(const std::exception &e)
		{
			std::cout<<"Exeption: ";
			std::cout<<e.what()<<std::endl;
		}
	}
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
	while(1)
	{

		it = lista.begin();
		while(it != lista.end())
		{
			it->sendRequest();
			if(it->getResponse() != "")
			{
				std::cout<<it->getResponse()<<std::endl;
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
	while(1)
	{
		std::cout<<"tick"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}
