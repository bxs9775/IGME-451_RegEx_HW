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

void DatumBase::print(std::ostream& output)
{
	output << "DatumBase object:" << std::endl;
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl << std::endl;
}
