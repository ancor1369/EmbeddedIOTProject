
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

	for(it = lista.begin(); it != lista.end(); it++)
	{
		it->sendRequest();
		std::cout<<it->getResponse()<<std::endl;
		if(it->getResponse() != "")
		{
			lista.erase(it);
		}
	}

	return 0;
}
