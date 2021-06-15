#pragma once
#include "ApiRest.h"
#include <string>

struct GetFileChangesEndPoint {
	void operator()(http_request request);
};


