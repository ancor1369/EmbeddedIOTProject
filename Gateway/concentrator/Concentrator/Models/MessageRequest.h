/*
 * MessageRequest.h
 *
 *  Created on: Apr. 11, 2020
 *      Author: andres
 */
#include <stdio.h>
#include <string>
#include "../restDriver/restDriver.h"

#define server "http://localhost:7000/"
//#define endpoint "demoProduct"
#define endpoint "productForLabel"


class MessageRequest {
public:
	MessageRequest(std::string reqObj, std::string snd);

	void sendRequest();

	std::string getResponse()
	{
		return response;
	}

	std::string getSender()
	{
		return sender;
	}

private:
	std::string requestObject;
	std::string sender;
	std::string response;
	restDriver driver;
};


