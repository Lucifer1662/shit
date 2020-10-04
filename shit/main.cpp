



#include <iostream>
#include <fstream>
#include "add.h"
#include "Commit.h"
#include "WorkingDirectory.h"
#include "Path.h"
#include <filesystem>


int main(int argn, char** argv) {

	char basePath[255];
	_fullpath(basePath, argv[0], sizeof(basePath));
	std::string workingDirectoryPath = basePath;
	auto index = workingDirectoryPath.rfind('\\');
	Shit::Path::workingDirectory = workingDirectoryPath.substr(0, index + 1);
	Shit::Path::workingDirectory += "test1\\";
	Shit::Path::shitDirectory = Shit::Path::workingDirectory + ".shit\\";
	Shit::Path::staging = Shit::Path::shitDirectory + "staging";
	Shit::Path::head = Shit::Path::shitDirectory + "head";
	Shit::Path::objectsDirectory = Shit::Path::shitDirectory + "objects\\";
	Shit::Path::snapshotDirectory = Shit::Path::shitDirectory + "snapshots\\";

	std::filesystem::create_directory(Shit::Path::shitDirectory);
	
	
	if (true)
	{
		std::fstream staging(Shit::Path::staging,
			std::fstream::in | std::fstream::out | std::fstream::app);

		std::vector<std::string> file_paths = {
			"Sorting1.c",
			"BigNum.c",
			"src\\Cube.c",
			"Sorting.c"};

		Add add = Add(staging);
		add(file_paths);
		staging.close();
	}

	int i = 0;
	//generate ref blobs
	//stage key for blobs

	{
	
		std::fstream staging(Shit::Path::staging,
			std::fstream::in | std::fstream::out);

		auto head = Snapshot::getHeadKey();
		std::vector<File::Key> parents;
		if (head.has_value()) {
			parents.push_back(head.value());
		}
		Commit commit(parents, staging, std::string("First Commit"));
		auto snapshot = commit();
		Snapshot::setHead(snapshot);

		staging.close();
	}

	{
		WorkingDirectory wd;
		if (!Snapshot::anyUntrackedChangesToHead())
			wd.PlaceSnapshotIn(Snapshot::getHead().value());
		else
			std::cout << "There are untracked changes" << std::endl;
	}
	return 0;
}