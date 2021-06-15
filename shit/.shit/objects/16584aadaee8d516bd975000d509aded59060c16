#include "Init.h"
#include <filesystem>
#include "Path.h"
#include <fstream>

namespace Shit {
	void Init::operator()() {
		std::filesystem::create_directory(Shit::Path::shitDirectory);
		std::filesystem::create_directory(Shit::Path::branchesDirectory);
		std::filesystem::create_directory(Shit::Path::objectsDirectory);
		std::filesystem::create_directory(Shit::Path::snapshotDirectory);
		std::ofstream head(Shit::Path::head);
		head << Shit::Path::branchesRelative + "master";
		head.close();
	}
}