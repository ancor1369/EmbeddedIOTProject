
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

//Data stecture to make test of threads
std::list<std::string> listaMessages;
std::list<std::string>::iterator itm;

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
	//Infine runnig thread,
	//This is to be administrated
	//by the operative system, I will set an
	//sleep function so that it does not high jack the processor
	while(1)
	{
		std::cin>>inputMessage;
		listaMessages.push_back(inputMessage);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void *processData(void * param)
{
	while(1)
	{
		for(itm = listaMessages.begin(); itm != listaMessages.end(); itm++)
		{
			std::cout<<*itm <<std::endl;
		}

		//Delete the processed messages;
		for(itm = listaMessages.begin(); itm != listaMessages.end(); itm++)
		{
			if(listaMessages.size()!=1)
			{
				listaMessages.erase(itm);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}




int main()
{
	//Simulate how the messages arrive to the system, they are
	//added to the container list and then the internal method is called
	//to make the actual request
//	parse.setRawMessage(message);
//	lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));
//	parse.setRawMessage(message1);
//	lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));
//
//
//	//This should be done in a different thread so that it is taking care of
//	//the pending, its job is to make sure the requests are done and taken back to
//	//the location where they belong to
//	while(lista.size()>0)
//	{
//		for(it = lista.begin(); it != lista.end(); it++)
//		{
//			it->sendRequest();
//			//This simulates the data sending facility
//			//over the UART interface
//			std::cout<<it->getResponse()<<std::endl;
//
//		}
//		//Remove those messages that are already responded
//		for(it = lista.begin(); it != lista.end(); it++)
//		{
//			if(it->getResponse() != "")
//			{
//				lista.erase(it);
//			}
//		}
//	}


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


	//Run for ever to keep the aplication alive
	while(1)
	{
		//std::cout<<"tick"<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}



	return 0;
}
