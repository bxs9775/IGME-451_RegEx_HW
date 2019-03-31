#pragma once

#include "ConfigVar.h"
#include<iostream>

#define MAX_STRING 9000

class DatumBase
{
public:
	DatumBase(ConfigVar::configVar vType);
	~DatumBase();

	//getters
	ConfigVar::configVar getVarType();

	//other
	std::string toString();
protected:
	ConfigVar::configVar varType;
};

