#include "Snapshot.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include "Path.h"
#include "WorkingDirectory.h"
#include <algorithm>

std::string Snapshot::toContent()
{
	std::stringstream content;
	for (auto& parent : parents) {
		content << parent << " ";
	}
	content << std::endl;
	for (auto& object : objects) {
		content << object.first.getKey() << " " << object.second << std::endl;
	}
	return content.str();
}

Snapshot::Snapshot(std::vector<std::pair<Object, Snapshot::Path>> objects, std::vector<File::Key> parents)
	: objects(objects),
	parents(parents),
	file(File::createFileFromContent(type, toContent())) {
}




std::optional<File::Key> Snapshot::getHeadKey()
{
	std::ifstream headFile(Shit::Path::head);
	std::string line;
	if (std::getline(headFile, line)) {
		return std::optional(line);
	}
	return std::optional<File::Key>();
}

std::optional<Snapshot> Snapshot::getHead() {
	auto key = getHeadKey();
	if (key.has_value()) {
		return fromKey(key.value());
	}
	return std::optional<Snapshot>();

}

void Snapshot::setHead(const Snapshot& snapshot)
{
	std::ofstream headFile(Shit::Path::head);
	headFile << snapshot.file.key;
}

Snapshot Snapshot::fromKey(std::string key)
{
	std::ifstream f(Shit::Path::snapshotDirectory + key);

	std::string parents_line;
	std::getline(f, parents_line);
	auto parents = getParentsFromString(parents_line);


	std::vector<std::pair<Object, Snapshot::Path>> objects;
	std::string line;
	while (std::getline(f, line)) {
		objects.push_back(getObjectAndPathFromString(line));
	}
	f.close();
	return Snapshot(objects, parents);
}

std::vector<File::Key> Snapshot::getParentsFromString(std::string line)
{
	std::vector<File::Key> result;
	std::istringstream iss(line);
	for (std::string s; iss >> s; ) {
		result.push_back(s);
	}
	return result;
}

std::pair<Object, Snapshot::Path> Snapshot::getObjectAndPathFromString(std::string line)
{
	int space_index = line.find_first_of(' ');
	auto key = line.substr(0, space_index);
	auto path = line.substr(space_index + 1);
	return std::make_pair(Object(key), path);
}



Snapshot Snapshot::createFromFile(Path path)
{



	return Snapshot();
}

bool Snapshot::anyUntrackedChangesTo(Snapshot snapshot)
{
	auto objects = WorkingDirectory::getFiles();
	for (auto& object : objects) {
		if (std::none_of(snapshot.objects.begin(), snapshot.objects.end(), [&](std::pair<Object, std::string> snap_obj) {
			if (snap_obj.second == object.second && snap_obj.first.getKey() == object.first) {
				return true;
			}
			return false;
		})) {
			return true;
		}
	}
	return false;
}

bool Snapshot::anyUntrackedChangesToHead()
{
	auto head = Snapshot::getHead();
	if (head.has_value()) {
		return anyUntrackedChangesTo(head.value());
	}
	return true;
}

