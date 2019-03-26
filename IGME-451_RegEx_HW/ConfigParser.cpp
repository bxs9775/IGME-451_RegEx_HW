#include "stdafx.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string path)
{
	lineIndex = 0;
	loadFile(path);
}

ConfigParser::~ConfigParser()
{
	/*
	if (path != nullptr) {
		delete config;
		config = nullptr;
	}
	*/
}

// main functions
ConfigParser::loadFile(std::string path)
{
	//config = new char[MAX_FILE_SIZE];
	std::ifstream file;
	std::string line;
	file.open(path);

	while (std::getline(file, line))
	{
		file += config;
	}

	return config;
}

ConfigParser::parseConfig()
{
	//Tokenize lines???
	std::string lines = std::sregex_token_iterator(config.begin(),config.end(), newLineRegex, 1);
	int numLines = lines.size();
	//lineIndex = 0;
	//Iterate through lines

	std::string currLine = "";

	for (int lineInd = 0; lineInd < numLines;i++) {
		currLine = lines[lineInd];
		std::cout << "Line " << lineInd << ": " << currLine << std::endl();
		
		// Remove comment (these can be ignored).
		std::cout << "[Removing comments...]" << std::endl();
		currLine = std::regex_relpace(currLine, commentRegex, "");
		std::cout << "Line " << lineInd << ": " << currLine << std::endl();

		// If there is only white space you can move on...
		std::cout << "[Checking whitespace...]" << std::endl();
		if (std::regex_match(currLine, blankLineRegex))
		{
			std::cout << "Line " << lineInd << " has been skipped.";
			break;
		}

		//Checking if this is a section.
		std::cout << "[Checking sections...]" << std::endl();
		std::smatch sectionsMatch;
		if (std::regex_match(currLine, sectionRegex)) {
			std::cout << "Line " << lineInd << " is a section.";
			std::cout << " -- count: " << sectionsMatch.count << std::endl();
			std::cout << " -- section: " << sectionsMatch[0] << std::endl();
			if (sectionsMatch.count > 1) {
				std::cout << " -- subsection: " << sectionsMatch[1] << std::endl();
			}
		}
	}
}