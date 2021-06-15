#pragma once
#include "ApiRest.h"
#include <string>

struct PutEndPoint {
	void operator()(http_request request);
};
