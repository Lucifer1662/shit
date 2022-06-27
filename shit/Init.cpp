#include "Init.h"
#include <filesystem>
#include "Path.h"
#include <fstream>

void Init::operator()() {
	std::filesystem::create_directory(shit.shitDirectory);
	std::filesystem::create_directory(shit.branchesDirectory);
	std::filesystem::create_directory(shit.objectsDirectory);
	std::filesystem::create_directory(shit.snapshotDirectory);
	std::ofstream head(shit.head);
	head << shit.branchesRelative + "master";
	head.close();
}