#pragma once
#include <vector>
#include <string>
#include <istream>


class Add
{	
	using stream = std::basic_iostream<char, std::char_traits<char>>;
	stream &staging;
	

public:
	Add(stream& staging);
	//adds the file_paths to the staging list
	void operator()(std::vector<std::string> file_paths);


	std::string generate_blob_key_value(std::string file);
};

