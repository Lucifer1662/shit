#pragma once
#include <string>
#include "Path.h"
#include <fstream>
#include <optional>
#include "File.h"
#include "Snapshot.h"
#include "Shit.h"

class Branch
{
	Shit& shit;
public:
	using Head = std::string;
	using Name = std::string;

private:
	Branch(Shit& shit, Name name, Head head) : shit(shit), name(name), head(head) {}

public:
	const Name name;
	const Head head;

	std::string getPath();

	static Branch createBranch(Shit& shit, Name name, Head head);




	static std::optional<File::Key> getHeadRef(Shit& shit);


	static std::optional<Branch> getBranchFromRef(Shit& shit, std::string ref);

	static std::optional<Branch> getBranch(Shit& shit, Name name);


	static std::optional<Branch> currentBranch(Shit& shit);

	void setHead();

	void setSnapshot(File::Key key);




};


