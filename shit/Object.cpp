#include "Object.h"
#include <functional>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "Path.h"


Object::Object(File::Key key): file(Object::type, key)
{
}

Object::Object(File file): file(file)
{
	
}

std::string Object::getPath() const {
	return Shit::Path::objectsDirectory + file.key;
}

File::Key Object::getKey() const
{
	return file.key;
}


Object Object::createFromPath(std::string path)
{
	return Object(File::createFileFromPath(Object::type, path));
}



