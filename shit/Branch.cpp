#include "Branch.h"
#include <iostream>

std::string Branch::getPath()
{
	return shit.branchesRelative + name;
}
Branch Branch::createBranch(Shit& shit, Name name, Head head) {
	std::ofstream branchFile(shit.head);
	branchFile << head;
	return Branch(shit, name, head);
}

std::optional<File::Key> Branch::getHeadRef(Shit& shit) {
	std::ifstream headFile(shit.head);
	std::string line;
	if (std::getline(headFile, line)) {
		return std::optional(line);
	}
	return std::optional<File::Key>();
}

std::optional<Branch> Branch::getBranchFromRef(Shit& shit, std::string ref) {
	auto index = ref.find_last_of('\\') + 1;
	auto name = ref.substr(index, ref.size() - index);
	std::cout << name << std::endl;
	return getBranch(shit, name);
}

std::optional<Branch> Branch::getBranch(Shit& shit, Name name) {
	std::ifstream branchFile(shit.branchesDirectory + name);
	std::string line;
	if (std::getline(branchFile, line)) {
		return std::optional(Branch(shit, name, line));
	}
	return std::optional(Branch(shit, name, ""));
}

std::optional<Branch> Branch::currentBranch(Shit& shit) {
	auto ref = Branch::getHeadRef(shit);
	if (ref) {
		std::cout << *ref << std::endl;
		return getBranchFromRef(shit, *ref);
	}
	return std::optional<Branch>();
}

void Branch::setHead()
{
	std::ofstream headFile(shit.head);
	headFile << shit.branchesRelative + name;
}

void Branch::setSnapshot(File::Key key)
{
	std::ofstream headFile(shit.branchesDirectory + name);
	headFile << key;
}
