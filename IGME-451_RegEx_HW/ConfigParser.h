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


#define DATA_MAP std::map<std::string,Section*>

#define INVALID_INPUT_ERROR(type,line,name) std::cerr << "Line " << line << ": Invalid " << type << " - " << name << std::endl;
#define SYMBOL_ERROR(line,symbol)  INVALID_INPUT_ERROR("symbol",line,symbol)
#define KEY_ERROR(line,key)  INVALID_INPUT_ERROR("key",line,key)
#define VALUE_ERROR(line,value)  INVALID_INPUT_ERROR("value",line,value)

class ConfigParser
{
public:
	// constructors
	///<summary>Initializes a ConfigParser object.</summary>
	///<param name="path">The path to the config file to be parsed.</param>
	ConfigParser(std::string path);

	///<summary>Deconstructs a deleted ConfigParser object.</summary>
	~ConfigParser();

	// main functions
	///<summary>Loads in a config file to parse.</summary>
	///<param name="path">The path to the config file to be loaded.</param>
	///<returns>The content of the file as a std::string object.</returns>
	std::string loadFile(std::string path);
	
	///<summary>Parses the current config file.</summary>
	///<returns>Boolean true if the file parsed without errors, or boolean false if parsing failed.</returns>
	bool parseConfig();

	///<summary>Parses the value of a key-value pair.</summary>
	///<param name="lineInd">The current line number (used for error reporting).</param>
	///<param name="key">The key of the key-value pair, used to store the parsed value in the correct place.</param>
	///<param name="value">The value of the key-value pair, what the function is parsing.</param>
	///<returns>Boolean true if the value parsed without errors, or boolean false if parsing failed.</returns>
	bool parseType(int lineInd, std::string key, std::string value);

	//Data getters
	///<summary>Determines if there is a section with the given name.</summary>
	///<param name="name">The name of the section to seach for.</param>
	///<returns>Boolean true if the section is found, boolean false if it isn't.</returns>
	bool SectionExists(std::string name);
	
	///<summary>Gets a list of sections on the top level of the parsed data structure.</summary>
	///<returns>A list containing pointers to the retrieved sections.</returns>
	std::list<Section*> ListAllSections();

	///<summary>Gets the section with the given name.</summary>
	///<param name="name">The name of the section to seach for.</param>
	///<returns>A pointer to the named section, or a nullpointer if it doesn't exist.<returns>
	Section* ListNamedSection(std::string name);

	///<summary>Gets the list of the subsections for a given section.</summary>
	///<param name="name">The name of the containing section.</param>
	///<returns>A list that contains pointers to the retrieved subsections, 
	///or an empty list if there are no subsections or the section doesn't exist.</returns>
	std::list<Section*> ListSubsections(std::string name);

	///<summary>Gets the subsection in the given section with the given name.</summary>
	///<param name="section">The name of the containing section.</param>
	///<param name="name">The name of the subsection to seach for.</param>
	///<returns>A pointer to the named subsection, or a nullpointer if it or the containing section doesn't exist.<returns>
	Section* ListNamedSubsection(std::string section, std::string name);

	///<summary>Gets a list of the entries for a section.</summary>
	///<param name="name">The name of the containing section.</param>
	///<returns>A list that contains the entities, or an empty list if there are no entities or the section doesn't exist.</returns>
	std::list<std::pair<std::string, DatumBase*>> ListAllEntries(std::string section);
	
	///<summary>Gets a list of the entries for a section and subsection.</summary>
	///<param name="section">The name of the containing section.</param>
	///<param name="subsection">The name of the containing subsection.</param>
	///<returns>A list that contains the entities, or an empty list if there are no entities or either the section or subsection don't exist.</returns>
	std::list<std::pair<std::string, DatumBase*>> ListAllEntries(std::string section, std::string subsection);
	
	///<summary>Gets an entry in the given section</summary>
	///<param name="section">The name of the containing section.</param>
	///<param name="key">The key for the entry.</param>
	///<returns>The entry as a pair object, or a default pair if the entry or section doesn't exist.</returns>
	std::pair<std::string, DatumBase*> GetEntry(std::string section, std::string key);

	///<summary>Gets an entry in the given section</summary>
	///<param name="section">The name of the containing section.</param>
	///<param name="subsection">The name of the containing subsection.</param>
	///<param name="key">The key for the entry.</param>
	///<returns>The entry as a pair object, or a default pair if the entry, section, or subsection doesn't exist</returns>
	std::pair<std::string, DatumBase*> GetEntry(std::string section, std::string subsection, std::string key);

	//Other functions
	///<summary>Prints the parsed data in a human friendly format.</summary>
	///<param name="out">The output stream to print to.</param>
	void print(std::ostream& out);
private:
	// Complete array of all the datatypes used in parsing values.
	ConfigVar::configVar fullAllowedTypes[6] = { ConfigVar::configVar::CONFIG_BOOLEAN_T, ConfigVar::configVar::CONFIG_FLOAT_T, ConfigVar::configVar::CONFIG_INT_T, ConfigVar::configVar::CONFIG_STRING_T, ConfigVar::configVar::CONFIG_LIST_T, ConfigVar::configVar::CONFIG_DEFAULT_T };
	// Complete array of all the datatypes used in parsing values within a list. The current parsing system does not allow nested lists.
	ConfigVar::configVar listAllowedTypes[5] = { ConfigVar::configVar::CONFIG_BOOLEAN_T, ConfigVar::configVar::CONFIG_FLOAT_T, ConfigVar::configVar::CONFIG_INT_T, ConfigVar::configVar::CONFIG_STRING_T, ConfigVar::configVar::CONFIG_DEFAULT_T };
	
	// regex objects used in parsing
	std::regex conVarRegex[6] = {
		// CONFIG_BOOLEAN_T regex
		std::regex("\\s*(true)\\s*|\\s*(false)\\s*", ECMAScript | icase),

		//CONFIG_INT_T regex
		std::regex("\\s*(\\d+)\\s*"),

		//CONFIG_FLOAT_T regex
		std::regex("\\s*(\\d*\\.\\d+f)\\s*"),

		//CONFIG_STRING_T regex
		std::regex("\\s*(\\\".*?[^\\\\]\\\"|\\\"\\\")(.*)"),
		
		//CONFIG_LIST_T regex
		//std::regex("\\{\\s*(.+)\\s*\\}"),
		std::regex("\\s*\\{(.+)\\}\\s*"),
		
		//CONFIG_DEFAULT_T regex
		std::regex("(\\s*)"),
	};
	std::regex newLineRegex = std::regex("\\n");
	std::regex commentRegex = std::regex("#.*$");
	std::regex blankLineRegex = std::regex("^\s*$");
	std::regex sectionRegex = std::regex("^\\[(\\w+)(?:\\:(\\w+))?\\]$");
	std::regex keyValueRegex = std::regex("^\\s*(.+?)\\s*=\\s*(.+)\\s*$");
	
	std::regex keyRegex = std::regex("\\w+");
	std::regex semiRegex = std::regex(";");
	
	//fields
	// Stores the parsed data.
	std::map<std::string, Section*> data;
	// Stores the loaded data to be parsed.
	std::string config;
	// Stores the name of the current section
	std::string section;
	// Stores the name of the current subsection
	std::string subsection;
};

