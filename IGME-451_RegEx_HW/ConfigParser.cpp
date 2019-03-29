#include "stdafx.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string path)
{
	data = new DATA_MAP();

	//lineIndex = 0;
	loadFile(path);
}

ConfigParser::~ConfigParser()
{
	if (data != nullptr) {
		delete data;
		data = nullptr;
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
		std::cout << "[Removing comments...]" << std::endl;
		currLine = std::regex_replace(currLine, commentRegex, "");
		std::cout << "Line " << lineInd << ": " << currLine << std::endl;

		// If there is only white space you can move on...
		std::cout << "[Checking whitespace...]" << std::endl;
		if (std::regex_match(currLine, blankLineRegex))
		{
			std::cout << "Line " << lineInd << " has been skipped." << std::endl;
			continue;
		}

		//Checking if this is a section.
		std::cout << "[Checking for sections...]" << std::endl;
		std::smatch sectionsMatch;
		if (std::regex_match(currLine, sectionsMatch, sectionRegex)) {
			std::cout << "Line " << lineInd << " is a section." << std::endl;
			std::cout << " -- section: " << sectionsMatch[1] << std::endl;
			std::cout << " -- subsection: " << sectionsMatch[2] << std::endl;

			section = sectionsMatch[1];
			subsection = sectionsMatch[2];
			if (SectionExists(section)) {
				if (subsection == "") {
					std::cerr << "Line " << lineInd << ": Section \"" << section << "\" already created.";
					return false;
				}
				if (!ListNamedSection(section).addSubsection(subsection)) {
					std::cerr << "Line " << lineInd << ": Subsection \"" << subsection << "\" already created.";
					return false;
				} 
				continue;
			}
			(*data)[section] = Section();
			continue;
		}

		//Checking if this is a key value pair.
		std::cout << "[Checking for key value pairs...]" << std::endl;
		std::smatch keyValueMatch;
		if (std::regex_match(currLine, keyValueMatch, keyValueRegex)) {
			std::cout << "Line " << lineInd << " is a key value pair." << std::endl;
			std::cout << " -- key: " << keyValueMatch[1] << std::endl;
			std::cout << " -- value: " << keyValueMatch[2] << std::endl;
			continue;
		}
	std::cout << std::endl;
	}
	return false;
}

bool ConfigParser::SectionExists(std::string name)
{
	return data->count(name);
}

std::list<Section> ConfigParser::ListAllSections()
{
	std::list<Section> sections;
	for (DATA_MAP::iterator iter = data->begin(); iter != data->end(); ++iter) {
		sections.push_back(iter->second);
	}
	return sections;
}

Section ConfigParser::ListNamedSection(std::string name)
{
	DATA_MAP::iterator sectionIter = data->find(name);
	if (sectionIter == data->end()) {
		return Section();
	}
	return sectionIter->second;
}
