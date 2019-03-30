#include "stdafx.h"
#include "Datum.h"


Datum::Datum(ConfigVar::configVar vType, std::string val):DatumBase(vType)
{
	value = val;
}


Datum::~Datum()
{
}

std::string Datum::getValue()
{
	return value;
}

void Datum::operator=(std::string val)
{
	value = val;
}
