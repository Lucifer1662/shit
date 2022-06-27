#pragma once
#include<vector>
#include<string>
#include"Object.h"
#include<fstream>
#include "File.h"
#include "Branch.h"
#include "Shit.h"

class Snapshot{
public:
	using Path = std::string;
	using InputStream = std::basic_istream<char, std::char_traits<char>>;
	using OutStream = std::basic_ostream<char, std::char_traits<char>>;
	const std::vector<std::pair<Object, Path>> objects;
	const File::Key previous;

private:
	
	
	
	File file;
	std::string toContent();
	Shit& shit;

public:
	
	std::string getPath();


	inline static const std::string type = "snapshots";


	Snapshot(Shit& shit, std::vector<std::pair<Object, Path>> objects = {}, File::Key previous = "");
	
	File::Key getKey();

	static std::optional<File::Key> getHeadKey(Shit& shit);
	static std::optional<Snapshot> getHead(Shit& shit);

	static Snapshot fromKey(Shit& shit,std::string file);

	static bool snapshotExists(Shit& shit,std::string key);

	//static Snapshot fromKey(std::string key);
	static std::pair<Object, Path> getObjectAndPathFromString(std::string);

	//create one from a file
	static Snapshot createFromFile(Shit& shit, Path path);
	//create one from another 
	//create one	
	static bool anyUntrackedChangesTo(const Snapshot& snapshot);
	static bool anyUntrackedChangesToHead(Shit& shit);

	static std::vector<Snapshot> snapShotsUpTo(Shit& shit,File::Key snapshot, File::Key oldSnapshot);

};

