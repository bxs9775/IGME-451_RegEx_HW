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
	
	/* Code below calls the ConfigParser's print() function to print all sections, 
	there are other methods for exploring the data.*/
	configParse.print(std::cout);
	//configParse.ListNamedSection("video")->print(std::cout);
	return 0;
}

