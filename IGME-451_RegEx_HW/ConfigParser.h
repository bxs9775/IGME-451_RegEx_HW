#pragma once

#include<list>
#include<string>
#include<map>
#include "Section.h"
#include "Datum.h"

#using std::string;
#using std::map;

class ConfigParser
{
public:
	// constructors
	ConfigParser();
	~ConfigParser();

	//Data getters
	std::list<Section> ListAllSections();
	Section ListNamedSection(string name);
	std::list<Section> ListSubsections(string name);
	std:list<std::pair<string, Datum>> ListAllEntries(string name);
	std::pair<string, Datum> GetEntry(string section, string key);

	//Other getters
	int getLine();
private:
	//fields
	int lineIndex;
	map<string, Section> data;
};

