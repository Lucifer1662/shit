#include "Branch.h"
#include <iostream>

namespace Shit {
	std::string Branch::getPath()
	{
		return Shit::Path::branchesRelative + name;
	}
	Branch Branch::createBranch(Name name, Head head) {
		std::ofstream branchFile(Shit::Path::head);
		branchFile << head;
		return Branch(name, head);
	}

	std::optional<File::Key> Branch::getHeadRef() {
		std::ifstream headFile(Shit::Path::head);
		std::string line;
		if (std::getline(headFile, line)) {
			return std::optional(line);
		}
		return std::optional<File::Key>();
	}

	std::optional<Branch> Branch::getBranchFromRef(std::string ref) {
		auto index = ref.find_last_of('\\')+1;
		auto name = ref.substr(index, ref.size() - index);
		std::cout << name << std::endl;
		return getBranch(name);
	}

	std::optional<Branch> Branch::getBranch(Name name) {
		std::ifstream branchFile(Shit::Path::branchesDirectory + name);
		std::string line;
		if (std::getline(branchFile, line)) {
			return std::optional(Branch(name, line));
		}
		return std::optional(Branch(name, ""));
	}

	std::optional<Branch> Branch::currentBranch() {
		auto ref = Branch::getHeadRef();
		if (ref) {
			std::cout << *ref << std::endl;
			return getBranchFromRef(*ref);
		}
		return std::optional<Branch>();
	}

	void Branch::setHead()
	{
		std::ofstream headFile(Shit::Path::head);
		headFile << Shit::Path::branchesRelative + name;
	}

	void Branch::setSnapshot(File::Key key)
	{
		std::ofstream headFile(Shit::Path::branchesDirectory + name);
		headFile << key;
	}
}
