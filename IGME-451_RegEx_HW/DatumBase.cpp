#include "stdafx.h"
#include "DatumBase.h"


DatumBase::DatumBase(std::string n, ConfigVar::configVar vType)
{
	name = n;
	varType = vType;
}


DatumBase::~DatumBase()
{
}

std::string DatumBase::getName()
{
	return name;
}

ConfigVar::configVar DatumBase::getVarType()
{
	return varType;
}

void DatumBase::print(std::ostream& output)
{
	output << "DatumBase - " << getName() << ":" << std::endl;
	//output << "DatumBase:" << std::endl;
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl << std::endl;
}
