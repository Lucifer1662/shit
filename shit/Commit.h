#pragma once
#include <fstream>
#include "Snapshot.h"
class Commit
{
	std::string message;
	File::Key previous;
public:
	Commit(File::Key previous, std::string message);
	Snapshot operator()();

};

