#pragma once

#include "ConfigVar.h"
#include<iostream>

class DatumBase
{
public:
	///<summary>Constructor for the DatumBase object.</summary>
	///<param name="n"> The name of the data. (The key).</param>
	///<param name="vType">What type of data is it. (See ConfigVar)</param>
	DatumBase(std::string n, ConfigVar::configVar vType);

	///<summary>Deconstructs a deleted DatumBase object.</summary>
	~DatumBase();

	//getters
	///<summary>Gets the name (key) of the DatumBase object.</summary>
	///<returns>The name as a std::string.</returns>
	std::string getName();

	///<summary> Gets the type of variable that is stored in this object.</summary>
	///<returns>A ConfigVar enum value.</summary>
	ConfigVar::configVar getVarType();

	//other
	///<summary>Prints the DatumBase object in a human friendly format.</summary>
	///<param name="out">The output stream to print to.</param>
	void print(std::ostream& output);
protected:
	std::string name;
	ConfigVar::configVar varType;
};

