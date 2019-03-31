#pragma once

#include "ConfigVar.h"
#include<iostream>

class DatumBase
{
public:
	DatumBase(ConfigVar::configVar vType);
	~DatumBase();

	//getters
	ConfigVar::configVar getVarType();

	//other
	void print (std::ostream& output);
protected:
	ConfigVar::configVar varType;
};

