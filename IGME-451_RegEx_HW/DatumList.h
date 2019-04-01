#pragma once
#include "DatumBase.h"

#include<list>
#include"Datum.h"

class DatumList :
	public DatumBase
{
public:
	///<summary>Constructor for the DatumList object.</summary>
	///<param name="vType">What type of data is it. (See ConfigVar)</param>
	///<param name="n"> The name of the data. (The key).</param>
	///<param name="val">A pointer to the list of data to be stored.</param>
	DatumList(std::string name,ConfigVar::configVar vType, std::list<Datum*>* val);
	
	///<summary>Deconstructs a deleted DatumList object.</summary>
	~DatumList();

	// getters
	///<summary>Gets  the stored data.</summary>
	///<returns>A pointer to a list of the data object pointers.</returns>
	std::list<Datum*>* getValue();

	//other
	///<summary>Prints the DatumList object in a human friendly format.</summary>
	///<param name="out">The output stream to print to.</param>
	void print(std::ostream& output);

private:
	//fields
	std::list<Datum*>* value;
};

