#pragma once
#include "DatumBase.h"

#include<list>
#include"Datum.h"

class DatumList :
	public DatumBase
{
public:
	DatumList(configVar vType, std::list<Datum> val);
	~DatumList();

	// getters
	std::list<Datum> getValue();

	//operator overrides
	void operator=(std::list<Datum> val);

private:
	//fields
	std::list<Datum> value;
};

