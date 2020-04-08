
#include "restDriver/restDriver.h"
#include "nlohmann/json.hpp"
#include "Models/MessageModels.h"



#define message "CA00{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"
#define messages "{\"CXT\":\"PRO\",\"Object\":{\"DeviceID\":\"01\"}}"

using json = nlohmann::json;


int main()
{
	restDriver driver;

	std::string server = "http://localhost:7000/";
	std::string endpoint = "/product/50";

	driver.setServer(server);
	driver.setEndPoint(endpoint);

	std::cout << driver.getMethod() << std::endl;
	std::cout<<message<<std::endl;


	std::string msg = message;
	std::string sender = msg.substr(0,4);

	std::cout << "this is the header of the message: " + sender << std::endl;

	std::string msgObject = msg.substr(4,msg.length());

	std::cout << "Trimmed message: " + msgObject << std::endl;

//	ms::incommingMessage p = {"PRO","{\"DeviceID\":\"01\"}"};
//
//	nlohmann::json jj = p;
//
//	std::cout << jj << std::endl;
//
//	std::cout<<"From created object"<<std::endl;
//	std::cout<<jj["Object"].get<std::string>()<<std::endl;
//
//	nlohmann::json internalObject = jj["Object"].get<std::string>();

	//auto inMessage = nlohmann::json::parse(messages);
	auto inMessage = nlohmann::json::parse(msgObject);

	std::cout<<"From parsed message"<<std::endl;
	std::cout<<inMessage["Object"].get<nlohmann::json>()<<std::endl;

	auto internal = inMessage["Object"].get<nlohmann::json>();
	std::cout << internal["DeviceID"].get<std::string>()<<std::endl;

	ms1::internalMessage inMsg = inMessage["Object"].get<ms1::internalMessage>();
	std::cout<<inMsg.DeviceID<<std::endl;

	return 0;
}
