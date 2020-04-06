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


std::string restDriver::getMethod()
{
	  std::string result;

	  http_client client(U(this->serverURL));
	  uri_builder builder(U(this->endpoint));

	  pplx::task<std::string> requestTask = client.request(methods::GET, builder.to_string()).then([](http_response response){
	    if(response.status_code() == status_codes::OK){
	      auto body = response.extract_string().get();
	      return body;
	    }});

	 requestTask.wait();

	 result = requestTask.get();
	 return result;
}
