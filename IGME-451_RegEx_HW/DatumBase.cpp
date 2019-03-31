#include "stdafx.h"
#include "DatumBase.h"


DatumBase::DatumBase(ConfigVar::configVar vType)
{
}


DatumBase::~DatumBase()
{
}

ConfigVar::configVar DatumBase::getVarType()
{
	return varType;
}

std::string DatumBase::toString()
{
	std::string strValue = "DatumBase object:\n";
	strValue.resize(MAX_STRING);

	strValue.append(" -- type: ");
	strValue.append(ConfigVar::conVarNames(getVarType()));
	strValue.append("\n\n");
	return strValue;
}