#pragma once
#include <string>
#include <optional>

class File{
public:
	using Stream = std::basic_iostream<char, std::char_traits<char>>;
	using Key = std::string;
	
private:
	
	std::string type;
	
public:
	File(std::string type, Key key);
	File(const File& file);
	const Key key;
	std::string getPath();
	static File createFileFromContent(std::string type, std::string content);
	static File createFileFromPath(std::string type, std::string path);
	static Key getKeyFromFile(std::string path);

};

