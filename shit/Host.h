#pragma once
#include "Path.h"
#include <filesystem>
#include "Server/RemoteServer.h"
#include "Shit.h"

class Host
{
	Shit& shit;

	

public:
	Host(Shit& shit) : shit(shit) {}
	void operator()()
	{
		std::cout << shit.objectsDirectory << std::endl;
		std::filesystem::create_directories(shit.objectsDirectory);
		startServer();
	}
};


