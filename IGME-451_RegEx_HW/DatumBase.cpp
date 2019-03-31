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

std::ostream & operator<<(std::ostream & output, DatumBase & data)
{
	output << "DatumBase object:" << std::endl;
	output << " -- type: " << ConfigVar::conVarNames(data.getVarType()) << std::endl << std::endl;
	return output;
}
