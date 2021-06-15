#include "Push.h"
#include "Shit.h"
#include <filesystem>
#include "Client/Client.h";

Push::Push(std::string remote) :remote(remote)
{
}

void Push::operator()()
{
	//get the head of remote of 
	auto headRef = Shit::Branch::getHeadRef();
	auto branch = Shit::Branch::currentBranch();

	if (headRef) {

		auto currentHeadSnapshot = branch->head;
		//get remote head
		auto remoteHeadSnapshot = getContent(remote, *headRef);


		//if the remote snapshot exists locally then we are ahead and can push new changes
		auto snapshots = Snapshot::snapShotsUpTo(currentHeadSnapshot, remoteHeadSnapshot);
		for (auto& snapshot : snapshots) {
			put(remote, snapshot.getPath());

			for (auto& object : snapshot.objects) {
				auto objectId = object.first;
				put(remote, objectId.getPath());
			}
		}

		if (snapshots.size() > 0) {
			put(remote, branch->getPath());
		}
	}


}
