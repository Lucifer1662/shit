
#include "ApiRest.h"
#include "GetEndPoint.h"
#include <iostream>
#include "strutil.h"
#include "CORS.h"


void GetEndPoint::operator()(http_request request) {

	auto fileStream = std::make_shared<concurrency::streams::istream>();
	auto queries = web::uri::split_query(request.relative_uri().query());

	std::wcout << "Get " << request.relative_uri().path() << std::endl;
	auto it = queries.find(U("path"));
	
	if (it != queries.end()) {
		auto key = web::uri::decode(it->second);
		std::wcout << key << std::endl;
		http_response res;
		res.set_status_code(http::status_codes::OK);
		addCors(res);
	
		try {
			std::cout << "Getting" << std::endl;
			// Open stream to input file.
			auto taskInput = concurrency::streams::fstream::open_istream(key);
			taskInput.wait();			
			res.set_body(taskInput.get());

		}
		catch (std::exception e) {
		}
		request.reply(res);
	}
	else {
		http_response res;
		res.set_status_code(http::status_codes::BadRequest);
		res.set_body(U("No Path Specified"));
		addCors(res);
		request.reply(res);
	}
}

