#pragma once
#include "DatumBase.h"

#include <string>

class Datum:
	public DatumBase
{
public:
	//constructor
	Datum(ConfigVar::configVar vType, std::string val);
	~Datum();

	// getters
	std::string getValue();

	//operator overrides
	void operator=(std::string val);
	friend std::ostream& operator<<(std::ostream& output, Datum& data);
private:
	//fields
	std::string value;
};

