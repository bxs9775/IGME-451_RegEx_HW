#pragma once

#include<string>
#include<map>
#include<list>
#include "DatumBase.h"

#define ENTRY std::pair<std::string, DatumBase*>

class Section
{
public:
	//constructors
	Section();
	~Section();

	//getters
	std::list<ENTRY> getEntries();
	std::list<ENTRY> getEntries(std::string subsection);
	ENTRY getEntry(std::string name);
	ENTRY getEntry(std::string subsection,std::string name);
	
	std::list<Section*> getSubsections();
	Section* getSubsection(std::string name);

	//adding functions
	void addPair(std::string key, DatumBase* value);
	void addPair(std::string subsection,std::string key, DatumBase* value);
	bool addSubsection(std::string name);
private:
	//fields
	std::map<std::string, DatumBase*> pairs;
	std::map<std::string, Section*> subsections;
};

