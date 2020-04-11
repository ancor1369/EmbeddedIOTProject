
//#include "restDriver/restDriver.h"
#include "nlohmann/json.hpp"
#include "Models/MessageModels.h"
#include "Models/MessageRequest.h"


#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define messages "{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"

using json = nlohmann::json;


int main()
{
    std::cout<<message<<std::endl;
	std::string msg = message;
	std::string sender = msg.substr(0,4);
	std::cout << "this is the header of the message: " + sender << std::endl;
	std::string msgObject = msg.substr(4,msg.length());
	std::cout << "Trimmed message: " + msgObject << std::endl;


	auto inMessage = nlohmann::json::parse(msgObject);
	std::cout<<"From parsed message"<<std::endl;
	std::cout<<inMessage["Object"].get<nlohmann::json>()<<std::endl;
	auto data = inMessage["Object"].get<nlohmann::json>();


	MessageRequest requester;

	//Put the JSON object here!
	requester.setRequestObject(data.dump());
	requester.setSender(sender.substr(0,1));

	requester.sendRequest();


	std::cout << requester.getResponse()<<std::endl;
	std::cout<< "This respose goes for the following device: " + requester.getSender() << std::endl;






	return 0;
}
