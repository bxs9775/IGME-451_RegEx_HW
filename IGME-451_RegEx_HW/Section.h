#pragma once

#include<string>
#include<map>
#include "Datum.h"

#using std::string;
#using std::map;

class Section
{
public:
	//constructors
	Section();
	~Section();

	//getters
	map<string, Datum> getPairs();
	map<string, Section> getSubsections();

	//adding functions
	void addPair(string key, Datum value);
	bool addSubsection(string name);
private:
	//fields
	map<string, Datum> pairs;
	map<string, Section> subsections;
};

