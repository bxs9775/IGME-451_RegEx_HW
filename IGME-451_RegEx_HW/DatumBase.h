#pragma once

#include "ConfigVar.h"

class DatumBase
{
public:
	DatumBase(configVar vType);
	~DatumBase();

	//getters
	configVar getVarType();
private:
	configVar varType;
};

