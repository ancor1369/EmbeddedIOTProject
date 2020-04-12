/*
 * MessageRequest.cpp
 *
 *  Created on: Apr. 11, 2020
 *      Author: andres
 */

#include "MessageRequest.h"

MessageRequest::MessageRequest(std::string reqObj, std::string snd) : requestObject(reqObj), sender(snd)
{
	this->response = "";
	this->sender=snd;
	this->requestObject=reqObj;
	driver.setServer(server);
	driver.setEndPoint(endpoint);
	driver.setJsonObjectString(reqObj);
}

void MessageRequest::sendRequest()
{
	//Make sure that the call can go OK before making it.
	if(this->sender == "")
	{
		//This is an error, I need a destiny to send the
		//message back
		return;
	}
	if(this->requestObject == "")
	{
		//This is an error, To be used as parameter of teh call
		//I will use in the API
		return;
	}
	response = driver.getMethod();
}

