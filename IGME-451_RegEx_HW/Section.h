#pragma once

#include<string>
#include<map>
#include "DatumBase.h"


class Section
{
public:
	//constructors
	Section();
	~Section();

	//getters
	std::map<std::string, DatumBase*> getPairs();
	std::map<std::string, Section*> getSubsections();

	//adding functions
	void addPair(std::string key, DatumBase* value);
	void addPair(std::string subsection,std::string key, DatumBase* value);
	bool addSubsection(std::string name);
private:
	//fields
	std::map<std::string, DatumBase*> pairs;
	std::map<std::string, Section*> subsections;
};

