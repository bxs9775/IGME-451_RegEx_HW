#include "stdafx.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string path)
{
	loadFile(path);
}

ConfigParser::~ConfigParser()
{
	for (std::map<std::string, Section*>::iterator dataIter = data.begin(); dataIter != data.end(); ++dataIter) {
		delete(dataIter->second);
	}
}

// main functions
std::string ConfigParser::loadFile(std::string path)
{
	std::ifstream file;
	std::string line;
	file.open(path);

	while (std::getline(file, line))
	{
		config += line + "\n";
	}

	return config;
}

bool ConfigParser::parseConfig()
{
	//Tokenize lines???
	std::vector<std::string> lines;
	auto lines_start = std::sregex_token_iterator(config.begin(), config.end(), newLineRegex, -1);
	auto lines_end = std::sregex_token_iterator();
	lines.assign(lines_start, lines_end);

	int numLines = lines.size();

	std::string currLine = "";

	for (int lineInd = 0; lineInd < numLines;lineInd++) {
		currLine = lines[lineInd];
		
		// Remove comments from config (these can be ignored).
		currLine = std::regex_replace(currLine, commentRegex, "");

		// If there is only white space you can move on...
		if (std::regex_match(currLine, blankLineRegex))
		{
			continue;
		}

		//Checking if this is a section.
		std::smatch sectionsMatch;
		if (std::regex_match(currLine, sectionsMatch, sectionRegex)) {
			section = sectionsMatch[1];
			subsection = sectionsMatch[2];
			if (SectionExists(section)) {
				if (subsection == "") {
					std::cerr << "Line " << lineInd << ": Section \"" << section << "\" was already created.";
					return false;
				}
				if (!ListNamedSection(section)->addSubsection(subsection)) {
					std::cerr << "Line " << lineInd << ": Subsection \"" << subsection << "\" was already created.";
					return false;
				}
				continue;
			}
			data[section] = new Section(section);
			if (subsection != "") {
				ListNamedSection(section)->addSubsection(subsection);
			}
			continue;
		}

		//Checking if this is a key value pair.
		std::smatch keyValueMatch;
		if (std::regex_match(currLine, keyValueMatch, keyValueRegex)) {
			if (section == "") {
				std::cerr << "Line " << lineInd << ": key-value pair created outside a section" << std::endl;
				return false;
			}
			std::string key = keyValueMatch[1];
			std::string value = keyValueMatch[2];
			if (!std::regex_match(key, keyRegex)) {
				KEY_ERROR(lineInd, key);
				return false;
			}
			if (!parseType(lineInd, key, value)) {
				return false;
			}

			continue;
		}
		SYMBOL_ERROR(lineInd, currLine);
		return false;
	}
	return true;
}

bool ConfigParser::parseType(int lineInd, std::string key, std::string value)
{
	// Loop through to check each variable type.
	for (int i = 0; i < 6; i++) {
		ConfigVar::configVar currVar = fullAllowedTypes[i];
		std::smatch varMatch;
		if (std::regex_match(value, varMatch, conVarRegex[(int)currVar])) {
			// The modified value for the data.
			std::string modVal = varMatch[1];

			// For the string regex to work properly, I had to do a greedy capture of anything after the second double quotation mark.
			// The program needs to check if this content is whitespace and throw an error if it isn't
			if (currVar == ConfigVar::configVar::CONFIG_STRING_T) {
				std::string extra = varMatch[2];
				if (!std::regex_match(extra, conVarRegex[(int)ConfigVar::configVar::CONFIG_DEFAULT_T])) {
					SYMBOL_ERROR(lineInd, extra)
					return false;
				}
			}
			// For lists, the program must parse the values within the list as well.
			if (currVar == ConfigVar::configVar::CONFIG_LIST_T) {
				bool valParsed = false;

				auto list_start = std::sregex_token_iterator(modVal.begin(), modVal.end(), semiRegex, -1);
				auto list_end = std::sregex_token_iterator();

				// Checks each item in the list.
				std::list<Datum*>* dataList = new std::list<Datum*>();
				for (std::sregex_token_iterator listIter = list_start; listIter != list_end; ++listIter) {
					valParsed = false;
					std::string listVal = listIter->str();

					// Checking against each non-list datatype.
					for (int j = 0; j < 5; j++) {
						ConfigVar::configVar currVar2 = listAllowedTypes[j];
						std::smatch varMatch2;
						if (std::regex_match(listVal, varMatch2, conVarRegex[(int)currVar2])) {
							// The modified value for the data.
							std::string modVal2 = varMatch2[1];
							if (currVar2 == ConfigVar::configVar::CONFIG_STRING_T) {
								std::string extra = varMatch2[2];
								if (!std::regex_match(extra, conVarRegex[(int)ConfigVar::configVar::CONFIG_DEFAULT_T])) {
									SYMBOL_ERROR(lineInd, extra)
									return false;
								}
							}
							// Once the value is parsed add a new Datum object to the list.
							Datum* data = new Datum(currVar2, modVal2);
							dataList->push_back(data);
							valParsed = true;
							continue;
						}
					}
					if (!valParsed) {
						VALUE_ERROR(lineInd, listVal)
						return false;
					}
				}
				// Create and add a new DatumList object to the data structure.
				DatumList* datumList = new DatumList(key, currVar, dataList);
				if (subsection == "") {
					ListNamedSection(section)->addPair(key, datumList);
				}
				else {
					ListNamedSection(section)->addPair(subsection, key, datumList);
				}
				// Return out of the function, or this value will be overwritten by a Datum object...
				return true;
			}
			// Create and add a new Datum object to the data structure.
			Datum* datum = new Datum(key, currVar, modVal);
			if (subsection == "") {
				ListNamedSection(section)->addPair(key, datum);
			}
			else {
				ListNamedSection(section)->addPair(subsection, key, datum);
			}
			// The value has been parsed, so the program can leave the function.
			return true;
		}
	}
	// If the value was correctly parsed the code won't reach this point.
	// Therefore any values making it this far are invalid.
	// Log an error and return false.
	VALUE_ERROR(lineInd, value)
	return false;
}

// getter functions
bool ConfigParser::SectionExists(std::string name)
{
	return data.count(name);
}

std::list<Section*> ConfigParser::ListAllSections()
{
	std::list<Section*> sections;
	for (DATA_MAP::iterator iter = data.begin(); iter != data.end(); ++iter) {
		sections.push_back(iter->second);
	}
	return sections;
}

Section* ConfigParser::ListNamedSection(std::string name)
{
	DATA_MAP::iterator sectionIter = data.find(name);
	if (sectionIter == data.end()) {
		return new Section();
	}
	return sectionIter->second;
}

std::list<Section*> ConfigParser::ListSubsections(std::string name)
{
	return ListNamedSection(name)->getSubsections();
}

Section * ConfigParser::ListNamedSubsection(std::string section, std::string name)
{
	return ListNamedSection(section)->getSubsection(name);
}

std::list<std::pair<std::string, DatumBase*>> ConfigParser::ListAllEntries(std::string section)
{
	return ListNamedSection(section)->getEntries();
}

std::list<std::pair<std::string, DatumBase*>> ConfigParser::ListAllEntries(std::string section, std::string subsection)
{
	return ListNamedSection(section)->getEntries(subsection);
}

std::pair<std::string, DatumBase*> ConfigParser::GetEntry(std::string section, std::string key)
{
	return ListNamedSection(section)->getEntry(key);
}

std::pair<std::string, DatumBase*> ConfigParser::GetEntry(std::string section, std::string subsection, std::string key)
{
	return ListNamedSection(section)->getEntry(subsection,key);
}

void ConfigParser::print(std::ostream & out)
{
	std::list<Section*> secs = ListAllSections();
	for (std::list<Section*>::iterator secIter = secs.begin(); secIter != secs.end(); ++secIter) {
		out << "Section: ";
		(*secIter)->print(out);
	}
}
