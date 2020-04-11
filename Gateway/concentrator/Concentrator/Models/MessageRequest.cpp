/*
 * MessageRequest.cpp
 *
 *  Created on: Apr. 11, 2020
 *      Author: andres
 */

#include "MessageRequest.h"

MessageRequest::MessageRequest() {
	//I initialize all the variables so that
	//They are all void to make sure I can test then before
	//calling the critical methods!
	this->response = "";
	this->sender="";
	this->requestObject="";
	driver.setServer(server);
	driver.setEndPoint(endpoint);
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

