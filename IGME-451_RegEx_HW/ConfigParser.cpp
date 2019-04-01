#include "stdafx.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string path)
{

	//lineIndex = 0;
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
	//config = new char[MAX_FILE_SIZE];
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
	//lineIndex = 0;
	//Iterate through lines

	std::string currLine = "";

	for (int lineInd = 0; lineInd < numLines;lineInd++) {
		currLine = lines[lineInd];
		std::cout << "Line " << lineInd << ": " << currLine << std::endl;
		
		// Remove comment (these can be ignored).
		std::cout << "Line " << lineInd << ": [Removing comments...]" << std::endl;
		currLine = std::regex_replace(currLine, commentRegex, "");
		std::cout << "Line " << lineInd << ": " << currLine << std::endl;

		// If there is only white space you can move on...
		std::cout << "Line " << lineInd << ": [Checking whitespace...]" << std::endl;
		if (std::regex_match(currLine, blankLineRegex))
		{
			std::cout << "Line " << lineInd << " has been skipped." << std::endl;
			continue;
		}

		//Checking if this is a section.
		std::cout << "Line " << lineInd << ": [Checking for sections...]" << std::endl;
		std::smatch sectionsMatch;
		if (std::regex_match(currLine, sectionsMatch, sectionRegex)) {
			std::cout << "Line " << lineInd << " is a section." << std::endl;
			std::cout << " -- section: " << sectionsMatch[1] << std::endl;
			std::cout << " -- subsection: " << sectionsMatch[2] << std::endl;

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
		std::cout << "Line " << lineInd << ": [Checking for key value pairs...]" << std::endl;
		std::smatch keyValueMatch;
		if (std::regex_match(currLine, keyValueMatch, keyValueRegex)) {
			std::cout << "Line " << lineInd << ": Line " << lineInd << " is a key value pair." << std::endl;
			std::cout << " -- key: " << keyValueMatch[1] << std::endl;
			std::cout << " -- value: " << keyValueMatch[2] << std::endl;
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
	std::cout << "[Begin value parsing]" << std::endl;
	
	for (int i = 0; i < 6; i++) {
		ConfigVar::configVar currVar = fullAllowedTypes[i];
		std::smatch varMatch;
		if (std::regex_match(value, varMatch, conVarRegex[(int)currVar])) {
			std::cout << "Line " << lineInd << " contains a variable of type " << ConfigVar::conVarNames(currVar) << "." << std::endl;
			// The modified value for the data.
			std::string modVal = varMatch[1];
			std::cout << "Line " << lineInd << ": captured value = " << modVal << std::endl;
			if (currVar == ConfigVar::configVar::CONFIG_STRING_T) {
				std::string extra = varMatch[2];
				if (!std::regex_match(extra, conVarRegex[(int)ConfigVar::configVar::CONFIG_DEFAULT_T])) {
					SYMBOL_ERROR(lineInd, extra)
					return false;
				}
			}

			if (currVar == ConfigVar::configVar::CONFIG_LIST_T) {
				//std::cout << "IS THIS RUNNING!!!" << std::endl;
				bool valParsed = false;

				auto list_start = std::sregex_token_iterator(modVal.begin(), modVal.end(), semiRegex, -1);
				auto list_end = std::sregex_token_iterator();

				std::list<Datum*>* dataList = new std::list<Datum*>();
				for (std::sregex_token_iterator listIter = list_start; listIter != list_end; ++listIter) {
					valParsed = false;
					std::string listVal = listIter->str();

					for (int j = 0; j < 5; j++) {
						ConfigVar::configVar currVar2 = listAllowedTypes[j];
						std::smatch varMatch2;
						if (std::regex_match(listVal, varMatch2, conVarRegex[(int)currVar2])) {
							std::cout << "Line " << lineInd << " contains a variable of type " << ConfigVar::conVarNames(currVar2) << "." << std::endl;
							// The modified value for the data.
							std::string modVal2 = varMatch2[1];
							std::cout << "Line " << lineInd << ": captured value = " << modVal2 << std::endl;
							if (currVar2 == ConfigVar::configVar::CONFIG_STRING_T) {
								std::string extra = varMatch2[2];
								if (!std::regex_match(extra, conVarRegex[(int)ConfigVar::configVar::CONFIG_DEFAULT_T])) {
									SYMBOL_ERROR(lineInd, extra)
									return false;
								}
							}
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
				DatumList* datumList = new DatumList(key, currVar, dataList);
				if (subsection == "") {
					ListNamedSection(section)->addPair(key, datumList);
				}
				else {
					ListNamedSection(section)->addPair(subsection, key, datumList);
				}
			}
			Datum* datum = new Datum(key, currVar, modVal);
			if (subsection == "") {
				ListNamedSection(section)->addPair(key, datum);
			}
			else {
				ListNamedSection(section)->addPair(subsection, key, datum);
			}
			return true;
		}
	}
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
