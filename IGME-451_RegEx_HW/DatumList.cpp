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

void DatumList::operator=(std::list<Datum> val)
{
	value = val;
}

std::ostream & operator<<(std::ostream & output, DatumList & data)
{
	output << "DatumList object:" << std::endl;
	output << " -- type: " << ConfigVar::conVarNames(data.getVarType()) << std::endl;
	output << " -- value: [";
	std::list<Datum> value = data.getValue();
	std::list<Datum>::iterator iter = value.begin();
	while (iter != value.end()) {
		output << iter->getValue();
		iter++;
		if (iter != value.end()) {
			output << ", ";
		}
	}
	output << "]" << std::endl << std::endl;
	return output;
}
