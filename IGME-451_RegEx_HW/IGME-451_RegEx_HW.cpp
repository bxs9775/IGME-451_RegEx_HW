// IGME-451_RegEx_HW.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<ostream>
#include "stdafx.h"
#include "ConfigParser.h"
#include "DatumBase.h"
#include "ConfigVar.h"

#define INPUT_FILE "input\\HW3_Ex_Config 2.txt"

int main()
{
	ConfigParser configParse = ConfigParser(INPUT_FILE);
	configParse.parseConfig();
	
	std::cout << std::endl << "-------------------------------------" << std::endl;
	//Temporary pair checking code...
	std::list<std::pair<std::string, DatumBase*>> pairs = configParse.ListNamedSection("globals")->getEntries();

	for (std::list<std::pair<std::string, DatumBase*>>::iterator pairIter = pairs.begin(); pairIter != pairs.end(); ++pairIter) {
		std::cout << "Key = " << pairIter->first << std::endl;
		DatumBase* value = pairIter->second;
		if (value->getVarType() == ConfigVar::configVar::CONFIG_LIST_T) {
			((DatumList*)value)->print(std::cout);
		}
		else {
			((Datum*)value)->print(std::cout);
		}
	}
	/**/
	return 0;
}

