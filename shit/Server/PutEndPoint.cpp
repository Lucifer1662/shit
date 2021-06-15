
#include "ApiRest.h"
#include "PutEndPoint.h"
#include <iostream>
#include "strutil.h"
#include "CORS.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "../Server/strutil.h"
#include <memory>
#include <filesystem>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using ostream = concurrency::streams::ostream;
using fstream = concurrency::streams::fstream;

void PutEndPoint::operator()(http_request request) {

	auto fileStream = std::make_shared<concurrency::streams::ostream>();
	auto queries = web::uri::split_query(request.relative_uri().query());

	std::wcout << "PUT " << request.relative_uri().path() << std::endl;
	auto it = queries.find(U("path"));
	if (it != queries.end()) {
		auto key = web::uri::decode(it->second);

		auto index = key.find_last_of('\\');
		if (index != std::wstring::npos) {
			std::filesystem::create_directories(key.substr(0, index));
		}	

	
		// Open stream to output file.
		concurrency::streams::fstream::open_ostream(key).then(
			[=](concurrency::streams::ostream outFile)
			{
				*fileStream = outFile;
				std::cout << "PUTTING" << std::endl;

				request.body().read_to_end(outFile.streambuf()).then([=](size_t) {
					fileStream->close();

					http_response res;
					res.set_status_code(http::status_codes::OK);
					addCors(res);
					request.reply(res);
				});
			});
	}
	else {		
		http_response res;
		res.set_status_code(http::status_codes::BadRequest);
		res.set_body(U("No Key Specified"));
		addCors(res);
		request.reply(res);
	}

	
}

