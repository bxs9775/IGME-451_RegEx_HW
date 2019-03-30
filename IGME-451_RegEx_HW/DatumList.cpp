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
