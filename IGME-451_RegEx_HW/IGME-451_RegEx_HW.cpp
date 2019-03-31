// IGME-451_RegEx_HW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include "ConfigParser.h"
#include "DatumBase.h"
#include "ConfigVar.h"

#define INPUT_FILE "input\\HW3_Test1.txt"
void printConfig(ConfigParser config) {
	std::list<Section*> sections = config.ListAllSections();
	for (std::list<Section*>::iterator secIter = sections.begin(); secIter != sections.end(); ++secIter) {
		Section* sec = (*secIter);
		std::cout << "Section: " << sec->toString() << std::endl << std::endl << std::endl;
	}
}

int main()
{
	ConfigParser configParse = ConfigParser(INPUT_FILE);
	configParse.parseConfig();
	
	std::cout << "-------------------------" << std::endl;

	//printConfig(configParse);
	std::cout << configParse.GetEntry("globals", "str1").second->toString();
	return 0;
}

