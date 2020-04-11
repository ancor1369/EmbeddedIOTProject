/*
 * restDriver.h
 *
 *  Created on: Apr. 6, 2020
 *      Author: andres
 */

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>


//using namespace std;
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


class restDriver {
private:

	std::string serverURL;
	std::string endpoint;
	std::string jsonParameterObject;

public:


	restDriver();
	virtual ~restDriver();

	//Methods to make API requests
	std::string getMethod();

	void setServer(std::string value)
	{
		serverURL = value;
	}

	void setEndPoint(std::string value)
	{
		endpoint = value;
	}

	void setJsonObjectString(std::string value)
	{
		jsonParameterObject = value;
	}

};


