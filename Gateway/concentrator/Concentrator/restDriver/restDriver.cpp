/*
 * restDriver.cpp
 *
 *  Created on: Apr. 6, 2020
 *      Author: andres
 */

#include "restDriver.h"

restDriver::restDriver() {
	// TODO Auto-generated constructor stub

}

restDriver::~restDriver() {
	// TODO Auto-generated destructor stub
}

//This single method makes the hard work to connect to the Rest API
//and send all the parameters to retreive the information saved in the
//database. Now it is an issue of using this code wisely to handle all the
//incoming messages.

std::string restDriver::getMethod()
{
	  std::string result;

	  http_client client(U(this->serverURL));
	  uri_builder builder(U(this->endpoint));


	  pplx::task<std::string> requestTask =
			  client.request(methods::GET, builder.to_string(),jsonParameterObject, "application/json; charset=utf-8", pplx::cancellation_token::none()).
			  then([](http_response response)
		{
			if(response.status_code() == status_codes::OK)
			{
			  auto body = response.extract_string().get();
			  return body;
	    }});

	 try
	 {
		 requestTask.wait();
		 result = requestTask.get();
	 }
	 catch(const std::exception &e)
	 {
		 std::cout << "Error: ";
		 std::cout<<e.what() << std::endl;
		 result = "";
	 }


	 return result;
}
