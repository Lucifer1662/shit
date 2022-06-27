#pragma once
#include "Shit.h"


class Init
{
	Shit& shit;
public:
	Init(Shit& shit) :shit(shit) {}
	void operator()();
};

