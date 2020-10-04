#include "Commit.h"
#include "Object.h"
#include <fstream>
#include <string>
#include <vector>
#include "Path.h"

Commit::Commit(std::vector<File::Key> parents, Commit::Stream& staging, std::string message):parents(parents), staging(staging), message(message)
{
}

Snapshot Commit::operator()()
{
	std::string file_path;
	std::vector<std::pair<Object, std::string>> objects;
	while (std::getline(staging, file_path)) {
		if (file_path != "") {
			//file_path = Shit::Path::workingDirectory + file_path;
			objects.push_back(std::make_pair(Object::createFromPath(file_path), file_path));
		}
	}
	staging << "";

	return Snapshot(objects, parents);
}
