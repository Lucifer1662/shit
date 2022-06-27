#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>


void setup();

void stage(const std::vector<std::string>& file_paths);

void commit(const std::string& message);


void changeWorkingDirectory(const std::string& branchName);

void changeWorkingDirectoryToHead();

void createBranch(const std::string& branchName);

struct Shit {
public:
	std::string workingDirectory;
	std::string shitDirectory;
	std::string staging;
	std::string head;
	std::string headRelative = ".shit\\head";

	std::string objectsDirectory;
	std::string objectsRelative = ".shit\\objects\\";
	std::string snapshotDirectory;
	std::string snapShotRelative = ".shit\\snapshots\\";
	std::string branchesDirectory;
	std::string branchesRelative = ".shit\\branches\\";

	Shit(const Shit&) = default;
	Shit(Shit&&) = default;

	Shit();
};


