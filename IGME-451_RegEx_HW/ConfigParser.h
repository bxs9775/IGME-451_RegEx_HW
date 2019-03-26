#pragma once

#include<list>
#include<string>
#include<map>
#include<regex>
#include<fstream>
#include<iostream>
#include "Section.h"
#include "Datum.h"

/**
#define MAX_INPUT = 9000
#define MAX_FILE_SIZE = MAX_INPUT * sizeof(char)
*/


class ConfigParser
{
public:
	// constructors
	ConfigParser(std::string path);
	~ConfigParser();

	// main functions
	std::string loadFile(std::string path);
	bool parseConfig();

	//Data getters
	std::list<Section> ListAllSections();
	Section ListNamedSection(std::string name);
	std::list<Section> ListSubsections(std::string name);
	std:list<std::pair<std::string, Datum>> ListAllEntries(std::string name);
	std::pair<std::string, Datum> GetEntry(std::string section, std::string key);

	//Other getters
	int getLine();
private:
	enum configVar = {
		CONFIG_BOOLEAN_T=0,
		CONFIG_INT_T=1,
		CONFIG_FLOAT_T=2,
		CONFIG_STRING_T=3,
		CONFIG_LIST_T=4,
		CONFIG_DEFAULT_T=5,
	};
	std::regex[] conVarRegex = [
		// CONFIG_BOOLEAN_T regex
		std::regex("true|false", ECMAScript | icase),
			//CONFIG_INT_T regex
			std::regex("\\d+"),
			//CONFIG_FLOAT_T regex
			std::regex("\\d.\\.\\d+"),
			//CONFIG_STRING_T regex
			std::regex("\\".*\\""),
			//CONFIG_LIST_T regex
			std::regex("[\\w*(\\W+)\\w*]"),
			//CONFIG_DEFAULT_T regex
			std::regex("\w*"),
	];
	std::regex newLineRegex("^.*?$");
	std::regex commentRegex("#.*$");
	std::regex blankLineRegex("^\w*$");
	//std::regex sectionRegex("^[\\s*(\\S+)\\s]$");
	std::regex sectionRegex("^\\[(\\w+)(?:\\:(\\w+))?\\]$");
	ste::regex keyValuePairRegex("^\\s*(\\w+)\\s*=\\s*(.+)\\s*$");
	//fields
	//int lineIndex;
	std::map<string, Section> data;
	std::string config;
	std::string section;
	std::string subsection;
};

