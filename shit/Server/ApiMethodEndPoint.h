#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <cpprest/http_msg.h>
#include "stdfx.h"


void NotFound(http_request msg);

class ApiMethodEndPoint
{


	std::unordered_map<Path, ApiHandle> paths;

	ApiHandle notFoundHandle = NotFound;

public:
	ApiMethodEndPoint() = default;
	ApiMethodEndPoint(ApiHandle&& notFoundHandle);
	ApiMethodEndPoint& addHandle(Path, ApiHandle&&);


	void invoke(http_request);
	void setNotFoundHandle(ApiHandle&&);



};

