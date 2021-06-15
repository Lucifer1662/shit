#pragma once
#include "Path.h"
#include "Branch.h"
#include <vector>
#include <iostream>
#include "add.h"


namespace Shit {
	void setup();

	void stage(const std::vector<std::string>& file_paths);

	void commit(const std::string& message);


	void changeWorkingDirectory(const std::string& branchName);

	void changeWorkingDirectoryToHead();

	void createBranch(const std::string& branchName);
}

