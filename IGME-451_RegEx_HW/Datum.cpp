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
std::ostream & operator<<(std::ostream& output, Datum & data)
{
	output << "Datum object:" << std::endl;
	output << " -- type: " << ConfigVar::conVarNames(data.getVarType()) << std::endl;
	output << " -- value: " << data.getValue() << std::endl << std::endl;
	return output;
}
