#pragma once
#include "DatumBase.h"

#include<list>
#include"Datum.h"

class DatumList :
	public DatumBase
{
public:
	DatumList(std::string name,ConfigVar::configVar vType, std::list<Datum> val);
	~DatumList();

	// getters
	std::list<Datum> getValue();

	//other
	void print(std::ostream& output);

private:
	//fields
	std::list<Datum> value;
};

