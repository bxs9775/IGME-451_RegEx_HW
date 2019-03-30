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

std::ostream & DatumBase::operator <<(std::ostream& output)
{
	output << "{";
	return output;
}
