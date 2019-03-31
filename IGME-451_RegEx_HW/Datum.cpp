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

void Datum::print(std::ostream& output)
{
	output << "Datum object:" << std::endl;
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl;
	output << " -- value: " << getValue() << std::endl << std::endl;
}
