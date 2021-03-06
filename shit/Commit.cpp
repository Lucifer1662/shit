#include "Commit.h"
#include "Object.h"
#include <fstream>
#include <string>
#include <vector>
#include "Path.h"

Commit::Commit(File::Key previous, std::string message):previous(previous), message(message)
{
}

Snapshot Commit::operator()()
{
	std::fstream staging(Shit::Path::staging, std::fstream::in);

	std::string file_path;
	std::vector<std::pair<Object, std::string>> objects;
	while (std::getline(staging, file_path)) {
		if (file_path != "") {
			//file_path = Shit::Path::workingDirectory + file_path;
			objects.push_back(std::make_pair(Object::createFromPath(file_path), file_path));
		}
	}
	staging.close();

	std::fstream st(Shit::Path::staging, std::fstream::out | std::fstream::trunc);
	st.close();
	

	return Snapshot(objects, previous);
}
