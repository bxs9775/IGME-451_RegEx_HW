#include "stdafx.h"
#include"ConfigVar.h"

std::string ConfigVar::conVarNames(configVar var)
{
	switch (var) {
		case configVar::CONFIG_BOOLEAN_T:
			return "CONFIG_BOOLEAN_T";
		case configVar::CONFIG_DEFAULT_T:
			return "CONFIG_DEFAULT_T";
		case configVar::CONFIG_INT_T:
			return "CONFIG_INT_T";
		case configVar::CONFIG_FLOAT_T:
			return "CONFIG_FLOAT_T";
		case configVar::CONFIG_STRING_T:
			return "CONFIG_STRING_T";
		case configVar::CONFIG_LIST_T:
			return "CONFIG_LIST_T";
	}
}
