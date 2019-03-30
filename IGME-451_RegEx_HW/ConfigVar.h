#pragma once
#include<iostream>
#include<regex>

static class ConfigVar {
public:
	static enum class configVar {
		CONFIG_BOOLEAN_T = 0,
		CONFIG_INT_T = 1,
		CONFIG_FLOAT_T = 2,
		CONFIG_STRING_T = 3,
		CONFIG_LIST_T = 4,
		CONFIG_DEFAULT_T = 5,
	};

	static std::string conVarNames(configVar var);
};