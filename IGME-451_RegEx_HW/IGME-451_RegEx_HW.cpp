// IGME-451_RegEx_HW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConfigParser.h"
#include "DatumBase.h"
#include "ConfigVar.h"

int main()
{
	ConfigParser configParse = ConfigParser("HW3_Ex_Config.txt");
	configParse.parseConfig();
	
	//Temporary pair checking code...
	std::map<std::string, DatumBase*> pairs = configParse.ListNamedSection("globals")->getPairs();

	for (std::map<std::string, DatumBase*>::iterator pairIter = pairs.begin(); pairIter != pairs.end(); ++pairIter) {
		std::cout << "Key = " << pairIter->first << std::endl;
		DatumBase* value = pairIter->second;
		std::cout << "Value = " << std::endl;
		//std::cout << " -- Type: " << value->getVarType() << std::endl;
		std::cout << value;
		//std::cout << " -- Value: " << ((Datum*)value)->getValue() << std::endl << std::endl;
	}
	return 0;
}

