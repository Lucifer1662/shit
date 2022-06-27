#pragma once
#include <string>
#include <optional>
#include "File.h"
#include "Shit.h"

class Object
{
	File file;
	Shit& shit;
public:
	inline static const std::string type = "Objects";
	Object(Shit& shit, File::Key key);
	Object(Shit& shit, File file);
	std::string getPath() const;
	File::Key getKey() const;

	static Object createFromPath(Shit& shit, std::string path);
};

