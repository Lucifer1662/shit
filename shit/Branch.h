#pragma once
#include <string>
#include "Path.h"
#include <fstream>
#include <optional>
#include "File.h"
#include "Snapshot.h"

namespace Shit {
	class Branch
	{
	public:
		using Head = std::string;
		using Name = std::string;

	private:
		Branch(Name name, Head head) : name(name), head(head) {}

	public:
		const Name name;
		const Head head;

		std::string getPath();

		static Branch createBranch(Name name, Head head);

	


		static std::optional<File::Key> getHeadRef();


		static std::optional<Branch> getBranchFromRef(std::string ref);

		static std::optional<Branch> getBranch(Name name);


		static std::optional<Branch> currentBranch();

		void setHead();

		void setSnapshot(File::Key key);
		

		

	};
}

