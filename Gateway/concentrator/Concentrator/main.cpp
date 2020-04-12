#include "nlohmann/json.hpp"
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"
#include "Models/Parser.h"

#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"

using json = nlohmann::json;
//This object will parse the raw incoming messages
//and will allow me to reuse it as more and more
//messages arrive.
Parser parse;

int main()
{
	parse.setRawMessage(message);

	//This section creates the object where I can save the messages
	//So that I can handle the information in this way.

	MessageRequest requester(parse.getParsedMsg(),parse.getSender());
	requester.sendRequest();

	std::cout << requester.getResponse()<<std::endl;
	std::cout<< "This respose goes for the following device: " + requester.getSender() << std::endl;

	//Starts implementation of the list to support all the incoming messages
	//that need to be processed on this device
	std::list<MessageRequest> lista;

	lista.push_back(requester);

	return 0;
}
