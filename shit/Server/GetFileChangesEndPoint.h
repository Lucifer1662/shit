#pragma once
#include "ApiRest.h"
#include <string>
#include "../Shit.h"

struct GetFileChangesEndPoint {
	Shit& shit;
	GetFileChangesEndPoint(Shit& shit): shit(shit){}
	void operator()(http_request request);
};


