
#include "restDriver/restDriver.h"


int main()
{

	restDriver driver;

	std::string server = "http://localhost:7000/";
	std::string endpoint = "/product/50";

	driver.setServer(server);
	driver.setEndPoint(endpoint);

	std::cout << driver.getMethod() << std::endl;


	    return 0;
}
