#include "Clone.h"
#include "Client/Client.h"
#include "WorkingDirectory.h"
#include "Snapshot.h"

void Clone::operator()(std::string url)
{
	getFiles(url, "", "master");
	auto snapshotOpt = Snapshot::getHead();
	if (snapshotOpt) {
		WorkingDirectory().PlaceSnapshotIn(*snapshotOpt);
	}
}
