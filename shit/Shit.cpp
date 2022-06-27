#include "Shit.h"
#include "Snapshot.h"
#include "Commit.h"
#include "WorkingDirectory.h"
#include <filesystem>
#include "Path.h"
#include "Branch.h"
#include "add.h"

void setup() {

}

void stage(const std::vector<std::string>& file_paths) {
	std::cout << "Starting Staging" << std::endl;

	Shit shit = Shit();

	std::fstream staging(shit.staging,
		std::fstream::in | std::fstream::out | std::fstream::app);

	/*std::vector<std::string> file_paths = {
	"Sorting1.c",
	"BigNum.c",
	"src\\Cube.c",
	"Sorting.c"
	};*/

	Add add = Add(staging);
	add(file_paths);
	staging.close();

	for (size_t i = 0; i < file_paths.size(); i++)
	{
		std::cout << '\t' << file_paths[i] << std::endl;
	}
	std::cout << "Staged" << std::endl << std::endl;
}

void commit(const std::string& message) {
	std::cout << "Starting Commit" << std::endl;

	Shit shit = Shit();

	std::fstream staging(shit.staging,
		std::fstream::in | std::fstream::out);

	auto head = Snapshot::getHeadKey(shit);
	std::string previous;
	if (head)
		previous = *head;

	Commit commit(shit, previous, message);
	auto snapshot = commit();

	staging.close();
}

void changeWorkingDirectory(const std::string& branchName) {
	Shit shit = Shit();
	if (!Snapshot::anyUntrackedChangesToHead(shit)) {
		auto branch = Branch::getBranch(shit, branchName);
		if (branch) {
			auto snapshot = Snapshot::fromKey(shit, branch->head);
			WorkingDirectory wd(shit);
			wd.PlaceSnapshotIn(snapshot);
		}
		else {
			std::cout << "No branch exists" << std::endl;
		}
	}
	else {
		std::cout << "There are untracked changes" << std::endl;
	}
}

void changeWorkingDirectoryToHead() {
	Shit shit = Shit();
	if (!Snapshot::anyUntrackedChangesToHead(shit)) {
		WorkingDirectory wd(shit);
		wd.PlaceSnapshotIn(Snapshot::getHead(shit).value());
	}
	else {
		std::cout << "There are untracked changes" << std::endl;
	}
}

void createBranch(Shit& shit, const std::string& branchName) {
	auto head = Snapshot::getHead(shit);
	if (head) {
		Branch::createBranch(shit, branchName, head->getKey());
	}
	else {
		Branch::createBranch(shit, branchName, "");
	}
}

inline Shit::Shit() {
	auto localPath = std::filesystem::current_path();

	workingDirectory = localPath.string() + "\\";
	shitDirectory = workingDirectory + ".shit\\";
	staging = shitDirectory + "staging";
	head = shitDirectory + "head";

	objectsDirectory = workingDirectory + objectsRelative;
	snapshotDirectory = workingDirectory + snapShotRelative;
	branchesDirectory = workingDirectory + branchesRelative;
}
