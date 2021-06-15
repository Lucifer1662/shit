#include "GetFileChangesEndPoint.h"
#include "ApiRest.h"
#include <iostream>
#include "strutil.h"
#include "CORS.h"
#include "../Snapshot.h"
#include "../RestUtil.h"
#include <filesystem>


template<typename T>
static T wait_get(Concurrency::task<T> task) {
	task.wait();
	return task.get();
}

void putFile(ostream& fileToSend, const std::string& path) {

	auto size = path.size();
	fileToSend.write((const char *)&size, sizeof(size_t));
	fileToSend << path;
	//wait_get(fileToSend.print(path));
	// Open stream to input file.
	auto taskInput = wait_get(concurrency::streams::fstream::open_istream(toUtilStr(path)));

	fileToSend << std::filesystem::file_size(path);
	fileToSend << taskInput;
}


void GetFileChangesEndPoint::operator()(http_request request) {

	auto fileStream = std::make_shared<concurrency::streams::istream>();
	auto queries = web::uri::split_query(request.relative_uri().query());

	std::wcout << "GetFileChanges " << request.relative_uri().path() << std::endl;
	auto changesSinceIt = queries.find(U("changesSince"));
	auto branchIt = queries.find(U("branch"));

	if (changesSinceIt != queries.end() && branchIt != queries.end()) {
		auto snapshot = web::uri::decode(changesSinceIt->second);
		auto branchName = web::uri::decode(branchIt->second);
		std::wcout << snapshot << " on  " << branchName << std::endl;

		http_response res;
		res.set_status_code(http::status_codes::OK);
		addCors(res);

		try {
			std::cout << "Getting changes" << std::endl;
			auto branch = Shit::Branch::getBranch(wsTos(branchName));
			if (branch) {
				auto snapshots = Snapshot::snapShotsUpTo(branch->head, wsTos(snapshot));

				std::filesystem::remove("temp");
				auto fileToSend = std::ofstream("temp", std::ios::binary);
				

				for (auto& snapshot : snapshots) {
					putFile(fileToSend, snapshot.getPath());

					for (auto& object : snapshot.objects) {
						auto objectId = object.first;
						putFile(fileToSend, objectId.getPath());
					}
				}

				fileToSend.close();
				auto ifileToSend = wait_get(concurrency::streams::fstream::open_istream(U("temp")));

				res.set_body(ifileToSend);
				
			}

		}
		catch (std::exception e) {
		}
		request.reply(res);
	}
	else {
		http_response res;
		res.set_status_code(http::status_codes::BadRequest);
		res.set_body(U("No snapshot since or no branch name"));
		addCors(res);
		request.reply(res);
	}
}

