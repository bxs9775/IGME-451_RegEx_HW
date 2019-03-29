#pragma once

#include<list>
#include<string>
#include<map>
#include<regex>
#include<fstream>
#include<iostream>
#include "Section.h"
#include "Datum.h"
#include "ConfigVar.h"

using namespace std::regex_constants;


/**
#define MAX_INPUT 9000
#define MAX_FILE_SIZE MAX_INPUT * sizeof(char)
*/
#define DATA_MAP std::map<std::string,Section*>

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
	bool SectionExists(std::string name);
	std::list<Section*> ListAllSections();
	Section* ListNamedSection(std::string name);
	std::list<Section*> ListSubsections(std::string name);
	std::list<std::pair<std::string, Datum*>> ListAllEntries(std::string name);
	std::pair<std::string, Datum*> GetEntry(std::string section, std::string key);

	//Other getters
	int getLine();
private:
	std::regex conVarRegex[6] = {
		// CONFIG_BOOLEAN_T regex
		std::regex("true|false", ECMAScript | icase),
		//CONFIG_INT_T regex
		std::regex("\\d+"),
		//CONFIG_FLOAT_T regex
		std::regex("\\d.\\.\\d+"),
		//CONFIG_STRING_T regex
		std::regex("\\\".*\\\""),
		//CONFIG_LIST_T regex
		std::regex("[\\w*(\\W+)\\w*]"),
		//CONFIG_DEFAULT_T regex
		std::regex("\w*"),
	};
	//std::regex newLineRegex = std::regex("^.*?$");
	std::regex newLineRegex = std::regex("\\n");
	std::regex commentRegex = std::regex("#.*$");
	std::regex blankLineRegex = std::regex("^\w*$");
	//std::regex sectionRegex = std::regex("^[\\s*(\\S+)\\s]$");
	std::regex sectionRegex = std::regex("^\\[(\\w+)(?:\\:(\\w+))?\\]$");
	std::regex keyValueRegex = std::regex("^\\s*(\\w+)\\s*=\\s*(.+)\\s*$");
	//fields
	//int lineIndex;
	std::map<std::string, Section*> data;
	std::string config;
	std::string section;
	std::string subsection;
};

