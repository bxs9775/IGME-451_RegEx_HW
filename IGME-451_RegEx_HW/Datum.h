#pragma once
#include "DatumBase.h"

#include <string>

class Datum:
	public DatumBase
{
public:
	//constructor
	Datum(ConfigVar::configVar vType, std::string val);
	Datum(std::string name, ConfigVar::configVar vType, std::string val);
	~Datum();

	// getters
	std::string getValue();

	//other
	void print(std::ostream& output);
private:
	//fields
	std::string value;
};

