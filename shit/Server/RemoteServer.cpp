#include <iostream>

#include "stdfx.h"
#include "handler.h"



#include "ApiRest.h"
#include "GetEndPoint.h"
#include "PutEndPoint.h"
#include "GetFileChangesEndPoint.h"
#include <mutex>

namespace Shit {


	void on_initialize(const string_t& address)
	{

		uri_builder uri(address);


		auto addr = uri.to_uri().to_string();
		apiHandler = std::make_unique<handler>(addr);

		apiHandler->addHandlePost(U("/put"), PutEndPoint());
		apiHandler->addHandleGet(U("/get"), GetEndPoint());
		apiHandler->addHandleGet(U("/getChanges"), GetFileChangesEndPoint());
		apiHandler->open().wait();



		ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

		return;
	}

	void on_shutdown(int d = 0)
	{
		apiHandler->close().wait();
	}

	std::mutex keepOpen;




	void startServer() {
		utility::string_t port = U("34568");

#ifdef _WIN32
		utility::string_t address = U("http://127.0.0.1:");
#else
		utility::string_t address = U("http://0.0.0.0:");
#endif


		address.append(port);

		on_initialize(address);
		std::cout << "Press ENTER to exit." << std::endl;




#ifdef _WIN32
		std::string line;
		std::getline(std::cin, line);
		on_shutdown();
#else
		while (true) {
			sleep(100000);
		}
		std::signal(SIGTERM, on_shutdown);
		std::signal(SIGKILL, on_shutdown);
#endif


	}
}