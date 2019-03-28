#pragma once

#include<string>
#include<map>
#include "Datum.h"


class Section
{
public:
	//constructors
	Section();
	~Section();

	//getters
	std::map<std::string, Datum> getPairs();
	std::map<std::string, Section> getSubsections();

	//adding functions
	void addPair(std::string key, Datum value);
	void addPair(std::string subsection,std::string key, Datum value);
	bool addSubsection(std::string name);
private:
	//fields
	std::map<std::string, Datum> pairs;
	std::map<std::string, Section> subsections;
};

