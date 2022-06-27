#include "Object.h"
#include <functional>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "Path.h"


Object::Object(Shit& shit, File::Key key): file(shit, Object::type, key), shit(shit)
{
}

Object::Object(Shit& shit, File file): file(file), shit(shit)
{
	
}

std::string Object::getPath() const {
	return shit.objectsRelative + file.key;
}

File::Key Object::getKey() const
{
	return file.key;
}


Object Object::createFromPath(Shit& shit, std::string path)
{
	return Object(shit, File::createFileFromPath(shit, Object::type, path));
}



