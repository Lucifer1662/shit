#pragma once
#include <string>
#include <optional>
#include "Shit.h"

class File{
public:
	using Stream = std::basic_iostream<char, std::char_traits<char>>;
	using Key = std::string;
	
private:
	
	std::string type;
	Shit& shit;
public:
	
	File(Shit& shit, std::string type, Key key);
	File(const File& file);
	const Key key;
	std::string getPath();
	static File createFileFromContent(Shit& shit, std::string type, std::string content);
	static File createFileFromPath(Shit& shit, std::string type, std::string path);
	static Key getKeyFromFile(Shit& shit, std::string path);

};

