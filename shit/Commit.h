#pragma once
#include <fstream>
#include "Snapshot.h"
class Commit
{
	std::string message;
	File::Key previous;
	Shit& shit;
public:
	Commit(Shit& shit, File::Key previous, std::string message);
	Snapshot operator()();

};

