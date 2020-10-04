#pragma once
#include <fstream>
#include "Snapshot.h"
class Commit
{
	using Stream = std::basic_iostream<char, std::char_traits<char>>;
	Stream& staging;
	std::string message;
	std::vector<File::Key> parents;
public:
	Commit(std::vector<File::Key>  parents, Stream& staging, std::string message);
	Snapshot operator()();

};

