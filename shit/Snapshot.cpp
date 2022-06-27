#include "Snapshot.h"
#include <sstream>
#include <fstream>
#include <string.h>
#include "Path.h"
#include "WorkingDirectory.h"
#include <algorithm>
#include "Branch.h"
#include <filesystem>

std::string Snapshot::toContent()
{
	std::stringstream content;
	content << previous << std::endl;

	for (auto& object : objects) {
		content << object.first.getKey() << " " << object.second << std::endl;
	}
	return content.str();
}

std::string Snapshot::getPath()
{
	return shit.snapShotRelative + getKey();
}

Snapshot::Snapshot(Shit& shit, std::vector<std::pair<Object, Snapshot::Path>> objects, File::Key previous)
	: objects(objects),
	previous(previous),
	shit(shit),
	file(File::createFileFromContent(shit, type, toContent())) {
}

inline File::Key Snapshot::getKey() { return file.key; }



std::optional<File::Key> Snapshot::getHeadKey(Shit& shit)
{
	auto ref = Branch::getHeadRef(shit);
	if (ref) {
		std::ifstream headFile(*ref);
		std::string line;
		if (std::getline(headFile, line)) {
			return std::optional(line);
		}
	}
	return std::optional<File::Key>();
}

std::optional<Snapshot> Snapshot::getHead(Shit& shit) {
	auto key = getHeadKey(shit);
	if (key.has_value()) {
		return fromKey(shit, key.value());
	}
	return std::optional<Snapshot>();

}



Snapshot Snapshot::fromKey(Shit& shit, std::string key)
{
	if (key == std::string("")) {
		return Snapshot(shit);
	}

	std::ifstream f(shit.snapshotDirectory + key);

	std::string previous;
	std::getline(f, previous);

	std::vector<std::pair<Object, Snapshot::Path>> objects;
	std::string line;
	while (std::getline(f, line)) {
		objects.push_back(getObjectAndPathFromString(line));
	}
	f.close();

	return Snapshot(shit, objects, previous);
}

bool Snapshot::snapshotExists(Shit& shit, std::string key)
{
	return std::filesystem::exists(shit.snapshotDirectory + key);
}


std::pair<Object, Snapshot::Path> Snapshot::getObjectAndPathFromString(std::string line)
{
	int space_index = line.find_first_of(' ');
	auto key = line.substr(0, space_index);
	auto path = line.substr(space_index + 1);
	return std::make_pair(Object(key), path);
}



Snapshot Snapshot::createFromFile(Shit& shit,Path path)
{
	return Snapshot(shit);
}

bool Snapshot::anyUntrackedChangesTo(const Snapshot& snapshot)
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

bool Snapshot::anyUntrackedChangesToHead(Shit& shit)
{
	auto head = Snapshot::getHead(shit);
	if (head.has_value()) {
		return anyUntrackedChangesTo(head.value());
	}
	return true;
}

std::vector<Snapshot> Snapshot::snapShotsUpTo(Shit& shit, File::Key snapshot, File::Key oldSnapshot)
{
	if (!Snapshot::snapshotExists(shit, snapshot)) {
		return {};
	}

	std::vector<Snapshot> snapshots;
	if (Snapshot::snapshotExists(shit, oldSnapshot) || oldSnapshot == "") {
		while (snapshot != oldSnapshot) {
			snapshots.push_back(Snapshot::fromKey(shit, snapshot));

			snapshot = snapshots.back().previous;
		}
	}

	return snapshots;
}

