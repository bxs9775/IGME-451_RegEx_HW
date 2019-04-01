#pragma once
#include "DatumBase.h"

#include <string>

class Datum:
	public DatumBase
{
public:
	//constructor
	///<summary>Constructor for the Datum object.</summary>
	///<param name="vType">What type of data is it. (See ConfigVar)</param>
	///<param name="val">A string representation of the value.</param>
	Datum(ConfigVar::configVar vType, std::string val);
	
	///<summary>Constructor for the Datum object.</summary>
	///<param name="vType">What type of data is it. (See ConfigVar)</param>
	///<param name="n"> The name of the data. (The key).</param>
	///<param name="val">A string representation of the value.</param>
	Datum(std::string name, ConfigVar::configVar vType, std::string val);

	///<summary>Deconstructs a deleted Datum object.</summary>
	~Datum();

	// getters
	///<summary>Gets a string representation of the stored value.</summary>
	///<returns>The value as a std::string.</returns>
	std::string getValue();

	//other
	///<summary>Prints the Datum object in a human friendly format.</summary>
	///<param name="out">The output stream to print to.</param>
	void print(std::ostream& output);
private:
	//fields
	std::string value;
};

