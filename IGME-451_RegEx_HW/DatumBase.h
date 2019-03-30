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
	std::ostream & operator <<(std::ostream& output);
private:
	ConfigVar::configVar varType;
};

