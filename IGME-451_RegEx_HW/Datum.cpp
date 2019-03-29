#include "stdafx.h"
#include "Datum.h"


Datum::Datum(configVar vType, std::string val)
{
	varType = vType;
	value = val;
}


Datum::~Datum()
{
}

configVar Datum::getVarType()
{
	return varType;
}

std::string Datum::getValue()
{
	return value;
}

void Datum::operator=(std::string val)
{
	value = val;
}
