
#include "restDriver/restDriver.h"


int main()
{

	restDriver driver;

	std::string server = "http://localhost:7000/";
	std::string endpoint = "/product/50";

	driver.setServer(server);
	driver.setEndPoint(endpoint);

	std::cout << driver.getMethod() << std::endl;

//Non workin

	//	pplx::create_task([]
//	{
//	    http_client client(U("http://localhost:7000/"));
//	    uri_builder builder(U("/product/50"));
//	    return client.request(methods::GET,builder.to_string());
//	}).then([](http_response response)
//	{
//	    if (response.status_code() == status_codes::OK)
//	    {
//	        auto body = response.extract_string();
//	        std::wcout << L"Added new Id: " << body.get().c_str() << std::endl;
//
//	        return std::stoi(body.get().c_str());
//	    }
//	});

	//Non workin


//	pplx::task<json::value> requestTask = pplx::create_task([]{
//			http_client client(U("http://localhost:7000/"));
//			// Build request URI and start the request.
//			uri_builder builder(U("/product/50"));
//			return client.request(methods::GET, builder.to_string());
//	}).then([](http_response response){
//		if(response.status_code() == status_codes::OK)
//		{
//		  return response.extract_json();
//		}
//		return pplx::create_task([] { return json::value(); });
//	}).then([] (json::value result){
//		return result;
//	});







	///Working code

	// Make the request and asynchronously process the response.


	//The following little piece of code is able to make get request to the service
	//This section compiles and work correctly!


//	  http_client client(U("http://localhost:7000/product/50"));
//
//	  client.request(methods::GET).then([](http_response response){
//	    if(response.status_code() == status_codes::OK){
//	      auto body = response.extract_string().get();
//	      std::cout << body<< std::endl;
//	    }}).wait();


	///Working code


//		auto fileStream = std::make_shared<ostream>();
//
//		// Open stream to output file.
//		pplx::task<void> requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
//		{
//			*fileStream = outFile;
//
//			// Create http_client to send the request.
//			http_client client(U("http://localhost:7000/"));
//			// Build request URI and start the request.
//			uri_builder builder(U("/product/50"));
//			return client.request(methods::GET, builder.to_string());
//		})
//
//		// Handle response headers arriving.
//		.then([=](http_response response)
//		{
//			printf("Received response status code:%u\n", response.status_code());
//
//	        auto body = response.extract_string();
//	        std::cout << body.get().c_str() << std::endl;
//
//			// Write response body into the file.
//			return response.body().read_to_end(fileStream->streambuf());
//
//		})
//
//	    // Close the file stream.
//	    .then([=](size_t)
//	    {
//	        return fileStream->close();
//	    });
////	     Wait for all the outstanding I/O to complete and handle any exceptions
//	    try
//	    {
//	        requestTask.wait();
//	    }
//	    catch (const std::exception &e)
//	    {
//	        printf("Error exception:%s\n", e.what());
//	    }



//	    char line[512];
//	    std::ifstream infile;
//	    infile.open("results.html");
//	    if(infile.is_open())
//	    {
//	    	infile.getline(line,512);
//	    	for(uint i = 0;i<sizeof(line);i++)
//	    	{
//	    		std::cout << line[i];
//	    	}
//
//	    	infile.close();
//	    }

	    return 0;
}
