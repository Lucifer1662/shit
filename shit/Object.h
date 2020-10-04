#pragma once
#include <string>
#include <optional>
#include "File.h"

class Object
{
	File file;

public:
	inline static const std::string type = "Objects";
	Object(File::Key key);
	Object(File file);
	std::string getPath() const;
	File::Key getKey() const;

	static Object createFromPath(std::string path);
};

