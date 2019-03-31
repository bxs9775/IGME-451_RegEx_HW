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

std::string DatumList::toString()
{
	std::string strValue = "DatumList object:\n";
	strValue.resize(MAX_STRING);

	strValue.append(" -- type: ");
	strValue.append(ConfigVar::conVarNames(getVarType()));
	strValue.append("\n");
	strValue.append(" -- value: [");
	std::list<Datum> value = getValue();
	std::list<Datum>::iterator iter = value.begin();
	while (iter != value.end()) {
		strValue.append(iter->getValue());
		iter++;
		if (iter != value.end()) {
			strValue.append(", ");
		}
	}
	strValue.append("]\n\n");
	return strValue;
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
