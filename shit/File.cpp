#include "File.h"
#include <functional>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "sha1.h"
#include "Path.h"

File::File(Shit& shit, std::string type, Key key): shit(shit), type(type), key(key)
{

}

File::File(const File& file): shit(file.shit), type(file.type), key(file.key)
{
}

std::string File::getPath() {
	return shit.shitDirectory + type+ "\\" + key;
}


File File::createFileFromPath(Shit& shit, std::string type, std::string path)
{
	auto key = getKeyFromFile(shit, path);


	std::filesystem::create_directories(shit.shitDirectory + type + "\\");
	std::filesystem::copy(shit.workingDirectory + path, shit.shitDirectory + type + "\\" + key, std::filesystem::copy_options::overwrite_existing);

	return File(shit, type, key);
}

File::Key File::getKeyFromFile(Shit& shit, std::string path)
{
	std::string content;
	std::fstream stream(shit.workingDirectory + path, std::fstream::in);
	std::string line;
	while (std::getline(stream, line)) {
		content += line;
	}
	stream.clear();
	stream.close();

	return sha1(content);
}

File File::createFileFromContent(Shit& shit, std::string type, std::string content)
{
	auto key = sha1(content);
	auto path = shit.shitDirectory + type + "\\";
	std::filesystem::create_directories(path );
	std::ofstream f(path + key);
	if(f.good())
		f << content;
	f.close();

	return File(shit, type, key);
}
