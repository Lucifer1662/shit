#pragma once
#include <string>
#include "Snapshot.h"
#include "Shit.h"

class WorkingDirectory
{
	Shit& shit;
public:
	WorkingDirectory(Shit& shit): shit(shit){}
	void PlaceSnapshotIn(const Snapshot& snapshot);

	static std::vector<std::pair<File::Key, std::string>> getFiles();
};

