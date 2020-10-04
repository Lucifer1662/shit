#include "Object.h"
#include <functional>
#include <fstream>
#include <string.h>
#include <filesystem>

Object::Object(std::string name): name(name)
{
}

std::string Object::getPath() {
	Key key = getKey();
	return OBJECT_PATH + std::to_string(key);
}

bool Object::exists(){
	
	auto key = getKey();
	std::ifstream f(std::to_string(key));
	bool exists = f.good();
	f.close();
	return exists;
}

Object::Key Object::create()
{
	auto key = getKey();
	if (!exists()) {
		std::filesystem::copy(name,
			OBJECT_PATH + std::to_string(key));
	}
	return key;
}

Object::Key Object::getKey()
{
	if (!key) {
		std::string content;
		std::fstream stream(name, std::fstream::in);
		std::string line;
		while (std::getline(stream, line)) {
			content += line;
		}
		stream.clear();
		stream.close();

		auto hasher = std::hash<std::string>();
		key = hasher(content);
	}

	return	key.value();
}
