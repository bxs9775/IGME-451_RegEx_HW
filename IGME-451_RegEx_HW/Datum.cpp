#include "stdafx.h"
#include "Datum.h"


Datum::Datum(ConfigVar::configVar vType, std::string val):Datum("",vType,val)
{
}

Datum::Datum(std::string name, ConfigVar::configVar vType, std::string val):DatumBase(name,vType)
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
	
	if (getName() != "") {
		output << "Datum - " << getName() << ":" << std::endl;
	}
	else {
		output << "Datum:" << std::endl;
	}
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl;
	output << " -- value: " << getValue() << std::endl << std::endl;
}
