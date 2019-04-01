#include "stdafx.h"
#include "DatumList.h"


DatumList::DatumList(std::string name, ConfigVar::configVar vType, std::list<Datum*>* val):DatumBase(name, vType)
{
	value = val;
}


DatumList::~DatumList()
{
	for (std::list<Datum*>::iterator iter = value->begin(); iter != value->end(); ++iter) {
		delete(*iter);
	}
	delete(value);
}

std::list<Datum*>* DatumList::getValue()
{
	return value;
}

void DatumList::print(std::ostream& output)
{
	output << "DatumList - " << getName() << ":" << std::endl;
	output << "DatumList:" << std::endl;
	output << " -- type: " << ConfigVar::conVarNames(getVarType()) << std::endl;
	output << " -- value: [";
	std::list<Datum*>* valList = getValue();
	std::list<Datum*>::iterator iter = valList->begin();
	while (iter != valList->end()) {
		output << (*iter)->getValue();
		iter++;
		if (iter != valList->end()) {
			output << ", ";
		}
	}
	output << "]" << std::endl << std::endl;
}
