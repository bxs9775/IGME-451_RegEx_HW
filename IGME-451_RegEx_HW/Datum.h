#pragma once

#include <string>
#include "ConfigVar.h"

#define GET

class Datum
{
public:
	//constructor
	Datum(configVar vType, std::string val);
	~Datum();

	// getters
	configVar getVarType();
	std::string getValue();

	//operator overrides
	void operator=(std::string val);

private:
	//fields
	configVar varType;
	std::string value;
};

