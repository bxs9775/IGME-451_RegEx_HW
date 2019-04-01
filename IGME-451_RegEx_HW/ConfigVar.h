#pragma once
#include<iostream>
#include<regex>

static class ConfigVar {
public:
	///<summary>An enum that keeps track the different datatypes that can be created in a config file.</summary>
	static enum class configVar {
		CONFIG_BOOLEAN_T = 0,
		CONFIG_INT_T = 1,
		CONFIG_FLOAT_T = 2,
		CONFIG_STRING_T = 3,
		CONFIG_LIST_T = 4,
		CONFIG_DEFAULT_T = 5,
	};

	///<summary>Takes a configVar enum and returns the correct string representation.</summary>
	///<param name=var>A configVar enum value to be translated into a string.</param>
	///<returns>A string representation for the configVar.</returns>
	static std::string conVarNames(configVar var);
};