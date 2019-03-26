#include "stdafx.h"
#include "ConfigParser.h"

ConfigParser::ConfigParser(std::string path)
{
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
		file += line;
	}

	return file;
}

ConfigParser::parseConfig()
{

}