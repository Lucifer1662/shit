



#include <iostream>
#include <fstream>
#include "add.h"
#include "Commit.h"
#include "WorkingDirectory.h"
#include "Path.h"
#include <filesystem>
#include "Shit.h"
#include "Commands.h"
#include <fstream>


int main(int argn, const char** argv) {

	Shit::setup();


	


	{
		Shit::Command command(argv[1], argv + 2, argn - 2);
		command.execute();
	}

	return 0;
	{
		const char* t[2] = { "d", "host" };
		int n = 2;

		Shit::Command command(t[1], t + 2, n - 2);
		command.execute();
	}

	return 0;
	/*{
		const char* t[3] = { "d", "add", "*" };
		int n = 3;

		Shit::Command command(t[1], t + 2, n - 2);
		command.execute();
	}

	{
		const char* t[4] = { "d", "commit", "-m", "This is a message" };
		int n = 4;

		Shit::Command command(t[1], t + 2, n - 2);
		command.execute();
	}*/

	//std::filesystem::remove_all(Shit::Path::shitDirectory);
	std::filesystem::create_directory(Shit::Path::shitDirectory);
	
	
	
	if (true)
	{
		
	}

	int i = 0;
	//generate ref blobs
	//stage key for blobs

	

	{
		WorkingDirectory wd;
		if (!Snapshot::anyUntrackedChangesToHead()) {
			auto head = Snapshot::getHead();
			if (head) {
				wd.PlaceSnapshotIn(*head);
			}
		}
		else
			std::cout << "There are untracked changes" << std::endl;
	}
	return 0;
}