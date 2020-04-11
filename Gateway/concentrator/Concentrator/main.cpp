
#include "restDriver/restDriver.h"
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

	MessageRequest requester;

	//Put the JSON object here!
	requester.setRequestObject("");
	requester.setSender("C");

	requester.sendRequest();

	return 0;
}
