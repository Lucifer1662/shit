#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "../Server/strutil.h"
#include <memory>
#include "../Path.h"
#include <stdlib.h> 
#include "Client.h"
#include <cpprest/rawptrstream.h>
#include <filesystem>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using ostream = concurrency::streams::ostream;
using fstream = concurrency::streams::fstream;

template<typename T>
static T wait_get(Concurrency::task<T> task) {
	task.wait();
	return task.get();
}


std::string getContent(std::string remotePath, std::string path)
{
	// Create http_client to send the request.
	http_client client(toUtilStr(remotePath));

	// Build request URI and start the request.
	uri_builder builder(U("/get"));
	builder.append_query(U("path"), toUtilStr(path));

	auto taskResponse = client.request(methods::GET, builder.to_string());
	taskResponse.wait();
	auto reponse = taskResponse.get();
	
	auto contentResponse = reponse.extract_string();
	contentResponse.wait();
	auto wContent = contentResponse.get();
	return std::string(wContent.begin(), wContent.end());
}


void get(std::string remotePath, std::string path)
{
	auto fileStream = std::make_shared<concurrency::streams::ostream>();

	// Open stream to output file.
	pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(toUtilStr(path)).then(
		[=](concurrency::streams::ostream outFile)
		{
			*fileStream = outFile;

			// Create http_client to send the request.
			http_client client(toUtilStr(remotePath));

			// Build request URI and start the request.
			uri_builder builder(U("/get"));
			//builder.append_query(U("q"), U("cpprestsdk github"));
			
			return client.request(methods::GET, builder.to_string());
		})

		// Handle response headers arriving.
		.then([=](http_response response)
		{
			printf("Received response status code:%u\n", response.status_code());

			// Write response body into the file.
			return response.body().read_to_end(fileStream->streambuf());
		})

		// Close the file stream.
		.then([=](size_t)
		{
			return fileStream->close();
		});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch (const std::exception& e)
	{
		printf("Error exception:%s\n", e.what());
	}
}

template<typename T> T read(Concurrency::streams::istream& stream) {
	T t;
	Concurrency::streams::rawptr_stream<char> s = Concurrency::streams::rawptr_stream<char>();
	auto ss = s.open_ostream((char*)&t, sizeof(T));

	
	try {
		wait_get(stream.read(ss.streambuf(), sizeof(T)));
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	ss.close();
	return t;
}

void read(Concurrency::streams::istream& stream, char* data, size_t size) {
	Concurrency::streams::rawptr_stream<char> s = Concurrency::streams::rawptr_stream<char>();
	auto ss = s.open_ostream(data, size);

	try {
		wait_get(stream.read(ss.streambuf(), size));
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	ss.close();
}

std::string get_string(Concurrency::streams::istream& stream, size_t size) {
	std::string path = std::string(size, ' ');
	read(stream, (char*)path.c_str(), size);
	return path;
}

std::string get_string(Concurrency::streams::istream& stream) {
	auto size =read<size_t>(stream);
	return get_string(stream, size);
}

void getFile(Concurrency::streams::istream& stream) {
	auto path = get_string(stream);
	auto file_size = read<size_t>(stream);

	
	std::filesystem::create_directories(path.substr(0, path.find_last_of('\\')));

	auto os = wait_get(concurrency::streams::fstream::open_ostream(toUtilStr(path))); 
	os.write(stream.streambuf(), file_size);
	os.close();
}


void getFiles(std::string remotePath, std::string snapshot, std::string branch)
{
	http_client client(toUtilStr(remotePath));

	uri_builder builder(U("/getChanges"));
	builder.append_query(U("changesSince"), toUtilStr(snapshot));
	builder.append_query(U("branch"), toUtilStr(branch));

	auto response = wait_get(client.request(methods::GET, builder.to_string()));
	auto stream = response.body();
	auto files = read<size_t>(stream);
	for(size_t i = 0; i < files; i++){
		getFile(stream);
	}
}

void put(std::string remotePath, std::string path)
{
	auto fileStream = std::make_shared<concurrency::streams::istream>();
	auto cancelToken = Concurrency::cancellation_token::none();

	

	// Open stream to output file.
	pplx::task<void> requestTask = concurrency::streams::fstream::open_istream(toUtilStr(path)).then(
		[=](concurrency::streams::istream outFile)
		{
			*fileStream = outFile;

		

			// Create http_client to send the request.
			http_client client(toUtilStr(remotePath));

			// Build request URI and start the request.
			uri_builder builder(U("/put"));
			builder.append_query(U("path"), toUtilStr(path));
			
			return client.request(methods::POST, builder.to_string(), outFile);
		})

		// Handle response headers arriving.
		.then([=](http_response response)
		{
			fileStream->close();
		});

		// Wait for all the outstanding I/O to complete and handle any exceptions
		try
		{
			requestTask.wait();
		}
		catch (const std::exception& e)
		{
			printf("Error exception:%s\n", e.what());
		}
}