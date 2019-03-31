// IGME-451_RegEx_HW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConfigParser.h"
#include "DatumBase.h"
#include "ConfigVar.h"

#define INPUT_FILE "input\\HW3_Test10.txt"

int main()
{
	ConfigParser configParse = ConfigParser(INPUT_FILE);
	configParse.parseConfig();
	
	/*
	//Temporary pair checking code...
	std::map<std::string, DatumBase*> pairs = configParse.ListNamedSection("globals")->getPairs();

	for (std::map<std::string, DatumBase*>::iterator pairIter = pairs.begin(); pairIter != pairs.end(); ++pairIter) {
		std::cout << "Key = " << pairIter->first << std::endl;
		DatumBase* value = pairIter->second;
		std::cout << "Value = " << std::endl;
		//std::cout << " -- Type: " << value->getVarType() << std::endl;
		//std::cout << (*value);
		if (value->getVarType() == ConfigVar::configVar::CONFIG_LIST_T) {
			std::list<Datum> valList = ((DatumList*)value)->getValue();
			std::list<Datum>::iterator iter = valList.begin();
			std::cout << " -- Value:[";
			while (iter != valList.end()) {
				std::cout << iter->getValue();
				iter++;
				if (iter != valList.end()) {
					std::cout << ", ";
				}
			}
			std::cout << "]" << std::endl << std::endl;
		}
		else {
			std::cout << " -- Value: " << ((Datum*)value)->getValue() << std::endl << std::endl;
		}
	}
	*/
	return 0;
}

