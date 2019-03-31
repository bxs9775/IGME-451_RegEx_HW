#include "stdafx.h"
#include "DatumList.h"


DatumList::DatumList(ConfigVar::configVar vType, std::list<Datum> val):DatumBase(vType)
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
	output << "DatumList object:" << std::endl;
	//output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl;
	output << " -- value: [";
	std::list<Datum> value = getValue();
	std::list<Datum>::iterator iter = value.begin();
	while (iter != value.end()) {
		output << iter->getValue();
		iter++;
		if (iter != value.end()) {
			output << ", ";
		}
	}
	output << "]" << std::endl << std::endl;
}
