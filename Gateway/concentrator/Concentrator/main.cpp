
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"
#include "Models/Parser.h"

#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define message1 "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"02\"}}"

using json = nlohmann::json;
//This object will parse the raw incoming messages
//and will allow me to reuse it as more and more
//messages arrive.
Parser parse;
std::list<MessageRequest> lista;
std::list<MessageRequest>::iterator it;

int main()
{
	//Simulate how the messages arrive to the system, they are
	//added to the container list and then the internal method is called
	//to make the actual request
	parse.setRawMessage(message);
	lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));
	parse.setRawMessage(message1);
	lista.push_back(MessageRequest(parse.getParsedMsg(),parse.getSender()));


	//This should be done in a different thread so that it is taking care of
	//the pending, its job is to make sure the requests are done and taken back to
	//the location where they belong to
	while(lista.size()>0)
	{
		for(it = lista.begin(); it != lista.end(); it++)
		{
			it->sendRequest();
			//This simulates the data sending facility
			//over the UART interface
			std::cout<<it->getResponse()<<std::endl;

		}
		//Remove those messages that are already responded
		for(it = lista.begin(); it != lista.end(); it++)
		{
			if(it->getResponse() != "")
			{
				lista.erase(it);
			}
		}
	}

	return 0;
}
