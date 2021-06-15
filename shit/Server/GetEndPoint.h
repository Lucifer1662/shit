#pragma once
#include "ApiRest.h"
#include <string>

struct GetEndPoint {
	void operator()(http_request request);
};
