#pragma once
#include <string>
#include "Snapshot.h"
class WorkingDirectory
{

public:
	void PlaceSnapshotIn(const Snapshot& snapshot);

	static std::vector<std::pair<File::Key, std::string>> getFiles();
};

