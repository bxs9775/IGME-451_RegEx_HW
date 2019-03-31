#include "stdafx.h"
#include "DatumList.h"


DatumList::DatumList(std::string name, ConfigVar::configVar vType, std::list<Datum> val):DatumBase(name, vType)
{
	value = val;
}


DatumList::~DatumList()
{
}

std::list<Datum> DatumList::getValue()
{
	return value;
}

void DatumList::print(std::ostream& output)
{
	output << "DatumList - " << getName() << ":" << std::endl;
	//output << "DatumList:" << std::endl;
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl;
	output << " -- value: [";
	std::list<Datum> val = getValue();
	std::list<Datum>::iterator iter = val.begin();
	while (iter != value.end()) {
		output << iter->getValue();
		iter++;
		if (iter != val.end()) {
			output << ", ";
		}
	}
	output << "]" << std::endl << std::endl;
}
