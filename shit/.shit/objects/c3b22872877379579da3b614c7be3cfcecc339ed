#include "File.h"
#include <functional>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "sha1.h"
#include "Path.h"

File::File(std::string type, Key key): type(type), key(key)
{

}

File::File(const File& file): type(file.type), key(file.key)
{
}

std::string File::getPath() {
	return Shit::Path::shitDirectory + type+ "\\" + key;
}


File File::createFileFromPath(std::string type, std::string path)
{
	auto key = getKeyFromFile(path);


	std::filesystem::create_directories(Shit::Path::shitDirectory + type + "\\");
	std::filesystem::copy(Shit::Path::workingDirectory + path, Shit::Path::shitDirectory + type + "\\" + key, std::filesystem::copy_options::overwrite_existing);

	return File(type, key);
}

File::Key File::getKeyFromFile(std::string path)
{
	std::string content;
	std::fstream stream(Shit::Path::workingDirectory + path, std::fstream::in);
	std::string line;
	while (std::getline(stream, line)) {
		content += line;
	}
	stream.clear();
	stream.close();

	return sha1(content);
}

File File::createFileFromContent(std::string type, std::string content)
{
	auto key = sha1(content);
	auto path = Shit::Path::shitDirectory + type + "\\";
	std::filesystem::create_directories(path );
	std::ofstream f(path + key);
	if(f.good())
		f << content;
	f.close();

	return File(type, key);
}
