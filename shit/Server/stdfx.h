#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#else
# include <sys/time.h>
#endif

#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <cpprest/producerconsumerstream.h>

#pragma warning ( push )
#pragma warning ( disable : 4457 )
#pragma warning ( pop )
#include <locale>
#include <ctime>

using http_request = web::http::http_request;
using ApiHandle = std::function<void(http_request)>;
using Path = utility::string_t;

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;