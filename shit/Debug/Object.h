#pragma once
#include <string>
#include <optional>

class Object
{
	inline static const std::string OBJECT_PATH = "C:\\Users\\lhawk\\OneDrive\\Projects\\shit\\Debug\\shit\\Objects\\";
	using Stream = std::basic_iostream<char, std::char_traits<char>>;
	using Key = size_t;
	std::string name;
	std::optional<Key> key;
	
public:
	Object(std::string name);
	bool exists();
	Key create();
	Key getKey();
	std::string getPath();
};

