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

std::string Datum::toString()
{
	std::string strValue = "DatumList object:\n";
	strValue.resize(MAX_STRING);

	strValue.append(" -- type: ");
	strValue.append(ConfigVar::conVarNames(getVarType()));
	strValue.append("\n");
	strValue.append(" -- value: ");
	strValue.append(getValue());
	strValue.append("\n\n");
	return strValue;
}