#pragma once

#include "ConfigVar.h"

class Datum
{
public:
	//constructor
	Datum();
	~Datum();

	// getters
	configVar getClass();
	template<typename T>
	T get();

	//operator overrides
	template<typename T>
	void operator=(T value);

private:
	//fields
	configVar classType;
	void* value;
};

