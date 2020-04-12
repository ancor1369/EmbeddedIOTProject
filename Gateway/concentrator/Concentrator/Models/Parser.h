/*
 * Parser.h
 *
 *  Created on: Apr. 11, 2020
 *      Author: Andres Cordoba
 *
 *      This class is designed to make sure the raw messages
 *      that arrive to the device are treated in a way that
 *      it is possible to obtain the internal message and
 *      then it is possible to get the correct information.
 *
 *      The message that arrives to this class, contains four
 *      initial characters that need to be removed and the
 *      first byte means the address where the response needs
 *      to be sent
 */

#ifndef MODELS_PARSER_H_
#define MODELS_PARSER_H_
#include <string>
#include "../nlohmann/json.hpp"

class Parser
{
private:
	std::string rawMsg;
	std::string sender;
	std::string parsedMsg;
	nlohmann::json inMessage;
	nlohmann::json internalObject;

public:
	void setRawMessage(std::string value)
	{
		rawMsg = value;
		sender = rawMsg.substr(0,1);
		parsedMsg = rawMsg.substr(4,rawMsg.length());
		inMessage = nlohmann::json::parse(parsedMsg);
		internalObject = inMessage["Object"].get<nlohmann::json>();
	}

	std::string getSender()
	{
		return sender;
	}

	std::string getParsedMsg()
	{
		return internalObject.dump();
	}
};

#endif /* MODELS_PARSER_H_ */
