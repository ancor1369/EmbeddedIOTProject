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
#define endpoint "demoProduct"


class MessageRequest {
public:
	MessageRequest();

	void sendRequest();

	void setRequestObject(std::string value)
	{
		requestObject = value;
	};

	void setSender(std::string value)
	{
		sender = value;
	}

	std::string getResponse()
	{
		return response;
	}


private:
	std::string requestObject;
	std::string sender;
	std::string response;
	restDriver driver;
};


