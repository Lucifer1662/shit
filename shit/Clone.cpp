#include "Clone.h"
#include "Client/Client.h"
#include "WorkingDirectory.h"
#include "Snapshot.h"
#include "Shit.h"

void Clone::operator()(std::string url)
{
	Shit shit = Shit();
	getFiles(url, "", "master");
	auto snapshotOpt = Snapshot::getHead(shit);
	if (snapshotOpt) {
		
		auto wd = WorkingDirectory(shit);
		wd.PlaceSnapshotIn(*snapshotOpt);
	}
}
