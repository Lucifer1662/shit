#pragma once
#include "Path.h"
#include <filesystem>
#include "Server/RemoteServer.h"

namespace Shit {
	class Host
	{
	public:
		void operator()()
		{
			std::cout << Shit::Path::objectsDirectory << std::endl;
			std::filesystem::create_directories(Shit::Path::objectsDirectory);
			startServer();
		}
	};
}

