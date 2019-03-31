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
	friend std::ostream& operator<<(std::ostream& output, DatumBase& data);
protected:
	ConfigVar::configVar varType;
};

