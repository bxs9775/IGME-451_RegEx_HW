#pragma once

#include<string>
#include<map>
#include<list>
#include "DatumBase.h"
#include "Datum.h"
#include "DatumList.h"

#define ENTRY std::pair<std::string, DatumBase*>

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
	Section* getSubsection(std::string subName);

	//adding functions
	void addPair(std::string key, DatumBase* value);
	void addPair(std::string subsection,std::string key, DatumBase* value);
	bool addSubsection(std::string subName);

	//other
	void print(std::ostream& out);
private:
	//fields
	std::string name;
	std::map<std::string, DatumBase*> pairs;
	std::map<std::string, Section*> subsections;
};

