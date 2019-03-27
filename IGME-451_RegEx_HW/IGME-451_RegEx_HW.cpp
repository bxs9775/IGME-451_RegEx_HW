// IGME-451_RegEx_HW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ConfigParser.h"

int main()
{
	ConfigParser configParse = ConfigParser("HW3_Ex_Config.txt");
	configParse.parseConfig();
	return 0;
}

