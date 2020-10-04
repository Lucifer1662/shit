#pragma once
#include<vector>
#include<string>
#include"Object.h"
#include<fstream>
#include "File.h"

class Snapshot{
public:
	using Path = std::string;
	using InputStream = std::basic_istream<char, std::char_traits<char>>;
	using OutStream = std::basic_ostream<char, std::char_traits<char>>;
	const std::vector<std::pair<Object, Path>> objects;
	const std::vector<File::Key> parents;

private:
	
	
	
	File file;
	std::string toContent();


public:
	
	inline static const std::string type = "snapshots";


	Snapshot(std::vector<std::pair<Object, Path>> objects = {}, std::vector<File::Key> parents = {});

	static std::optional<File::Key> getHeadKey();
	static std::optional<Snapshot> getHead();
	static void setHead(const Snapshot& snapshot);
	static Snapshot fromKey(std::string file);
	//static Snapshot fromKey(std::string key);
	static std::vector<File::Key> getParentsFromString(std::string);
	static std::pair<Object, Path> getObjectAndPathFromString(std::string);
	//create one from a file
	static Snapshot createFromFile(Path path);
	//create one from another 
	//create one	
	static bool anyUntrackedChangesTo(Snapshot snapshot);
	static bool anyUntrackedChangesToHead();
};

