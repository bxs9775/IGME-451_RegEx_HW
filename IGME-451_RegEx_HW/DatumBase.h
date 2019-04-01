#pragma once

#include "ConfigVar.h"
#include<iostream>

class DatumBase
{
public:
	DatumBase(std::string n, ConfigVar::configVar vType);
	~DatumBase();

	//getters
	std::string getName();
	ConfigVar::configVar getVarType();

	//other
	void print(std::ostream& output);
protected:
	std::string name;
	ConfigVar::configVar varType;
};

