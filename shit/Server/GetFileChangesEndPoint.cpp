#include "GetFileChangesEndPoint.h"
#include "ApiRest.h"
#include <iostream>
#include "strutil.h"
#include "CORS.h"
#include "../Snapshot.h"
#include "../RestUtil.h"
#include <filesystem>
#include <cpprest/rawptrstream.h>


template<typename T>
static T wait_get(Concurrency::task<T> task) {
	task.wait();
	return task.get();
}

template<typename T> 
void write(Concurrency::streams::ostream& stream, const T& t) {
	Concurrency::streams::rawptr_stream<char> s = Concurrency::streams::rawptr_stream<char>();
	auto ss = s.open_istream((char*)&t, sizeof(T));


	try {
		wait_get(stream.write(ss.streambuf(), sizeof(T)));
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	ss.close();
}

void putFile(Concurrency::streams::ostream& fileToSend, const std::string& path) {

	
	
	auto size = path.size();
	write(fileToSend, size);
	fileToSend.print(path);

	/*fileToSend.write((const char *)&size, sizeof(size_t));
	fileToSend << path;*/
	// Open stream to input file.
	auto taskInput = wait_get(concurrency::streams::fstream::open_istream(toUtilStr(path)));

	size_t fileSize = std::filesystem::file_size(path);
	//fileToSend.write((const char*)&fileSize, sizeof(size_t));

	write(fileToSend,fileSize);
	taskInput.read_to_end(fileToSend.streambuf());
	
	
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
			auto branch = Branch::getBranch(shit, wsTos(branchName));
			if (branch) {
				auto snapshots = Snapshot::snapShotsUpTo(shit, branch->head, wsTos(snapshot));

				std::filesystem::remove("temp");
				auto fileToSend = wait_get(Concurrency::streams::fstream().open_ostream(U("temp"), std::ios_base::binary));
					//std::ofstream("temp", std::ios::binary);
				
				size_t files = 2;
				for (auto& snapshot : snapshots) {
					files += snapshot.objects.size() + 1;
				}

				write<size_t>(fileToSend, files);

				putFile(fileToSend, branch->getPath());
				putFile(fileToSend, shit.headRelative);



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

