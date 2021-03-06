#include "../nlohmann/json.hpp"



namespace ms
{


	struct incommingMessage
	{
		std::string cxt;
		std::string object;
	};

	void to_json(nlohmann::json& j, const incommingMessage& im)
	{
		j = nlohmann::json{{"CXT", im.cxt},{"Object", im.object}};
	}

	void from_json(const nlohmann::json& j, incommingMessage& im)
	{
		j.at("CXT").get_to(im.cxt);
		j.at("Object").get_to(im.object);
	}
}

namespace ms1
{
	struct internalMessage
	{
		std::string DeviceID;
	};

	void to_json(nlohmann::json& j, const internalMessage& im)
	{
		j = nlohmann::json{{"DeviceID", im.DeviceID}};
	}

	void from_json(const nlohmann::json& j, internalMessage& im)
	{
		j.at("DeviceID").get_to(im.DeviceID);
	}

}
