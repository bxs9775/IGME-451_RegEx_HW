#pragma once

#include<string>
#include<map>
#include<list>
#include "DatumBase.h"

#define ENTRY std::pair<std::string, DatumBase*>
#define MAX_STRING 9000

class Section
{
public:
	//constructors
	Section();
	Section(std::string name);
	~Section();

	//getters
	std::string getName();
	std::list<ENTRY> getEntries();
	std::list<ENTRY> getEntries(std::string subsection);
	ENTRY getEntry(std::string key);
	ENTRY getEntry(std::string subsection,std::string key);
	
	std::list<Section*> getSubsections();
	Section* getSubsection(std::string subsection);

	//adding functions
	void addPair(std::string key, DatumBase* value);
	void addPair(std::string subsection,std::string key, DatumBase* value);
	bool addSubsection(std::string subsection);

	//other
	std::string toString();
private:
	//fields
	std::string name;
	std::map<std::string, DatumBase*> pairs;
	std::map<std::string, Section*> subsections;
};

