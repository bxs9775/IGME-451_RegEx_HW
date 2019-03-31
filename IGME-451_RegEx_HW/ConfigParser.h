#pragma once

#include<list>
#include<string>
#include<map>
#include<regex>
#include<fstream>
#include<iostream>
#include "Section.h"
#include "Datum.h"
#include "DatumList.h"
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
	bool parseType(int lineInd, std::string key, std::string value);

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
	ConfigVar::configVar fullAllowedTypes[6] = { ConfigVar::configVar::CONFIG_BOOLEAN_T, ConfigVar::configVar::CONFIG_FLOAT_T, ConfigVar::configVar::CONFIG_INT_T, ConfigVar::configVar::CONFIG_STRING_T, ConfigVar::configVar::CONFIG_LIST_T, ConfigVar::configVar::CONFIG_DEFAULT_T };
	ConfigVar::configVar listAllowedTypes[5] = { ConfigVar::configVar::CONFIG_BOOLEAN_T, ConfigVar::configVar::CONFIG_FLOAT_T, ConfigVar::configVar::CONFIG_INT_T, ConfigVar::configVar::CONFIG_STRING_T, ConfigVar::configVar::CONFIG_DEFAULT_T };
	std::regex conVarRegex[6] = {
		// CONFIG_BOOLEAN_T regex
		std::regex("\\s*(true)\\s*|\\s*(false)\\s*", ECMAScript | icase),
		//CONFIG_INT_T regex
		std::regex("\\s*(\\d+)\\s*"),
		//CONFIG_FLOAT_T regex
		std::regex("\\s*(\\d*\\.\\d+f)\\s*"),
		//CONFIG_STRING_T regex
		std::regex("\\s*(\\\".*\\\")\\s*"),
		//CONFIG_LIST_T regex
		//std::regex("\\{\\s*(.+)\\s*\\}"),
		std::regex("\\s*\\{(.+)\\}\\s*"),
		//CONFIG_DEFAULT_T regex
		std::regex("(\\s*)"),
	};
	//std::regex newLineRegex = std::regex("^.*?$");
	std::regex newLineRegex = std::regex("\\n");
	std::regex commentRegex = std::regex("#.*$");
	std::regex blankLineRegex = std::regex("^\w*$");
	//std::regex sectionRegex = std::regex("^[\\s*(\\S+)\\s]$");
	std::regex sectionRegex = std::regex("^\\[(\\w+)(?:\\:(\\w+))?\\]$");
	std::regex keyValueRegex = std::regex("^\\s*(\\w+)\\s*=\\s*(.+)\\s*$");
	std::regex semiRegex = std::regex(";");
	//fields
	//int lineIndex;
	std::map<std::string, Section*> data;
	std::string config;
	std::string section;
	std::string subsection;
};

