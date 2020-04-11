
//#include "restDriver/restDriver.h"
#include "nlohmann/json.hpp"
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"


#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define messages "{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"

using json = nlohmann::json;


int main()
{
	//This code filters the incoming messages and separates the parts that
	//I need to process the packet, I need to un assemble it as it comes
	std::cout<<message<<std::endl;
	std::string msg = message;
	std::string sender = msg.substr(0,4);
	std::cout << "this is the header of the message: " + sender << std::endl;
	std::string msgObject = msg.substr(4,msg.length());
	std::cout << "Trimmed message: " + msgObject << std::endl;


	//This section prepares the actual JSON object
	auto inMessage = nlohmann::json::parse(msgObject);
	std::cout<<"From parsed message"<<std::endl;
	std::cout<<inMessage["Object"].get<nlohmann::json>()<<std::endl;
	auto data = inMessage["Object"].get<nlohmann::json>();


	//This section creates the object where I can save the information
	//So that I can handle the information in this way.
	MessageRequest requester;
	//Put the JSON object here!
	requester.setRequestObject(data.dump());
	requester.setSender(sender.substr(0,1));
	requester.sendRequest();

	std::cout << requester.getResponse()<<std::endl;
	std::cout<< "This respose goes for the following device: " + requester.getSender() << std::endl;

	//Starts inplementation of the list to support all the incoming messages
	//that need to be processed on this device
	std::list<MessageRequest> lista;

	lista.push_back(requester);




	return 0;
}
