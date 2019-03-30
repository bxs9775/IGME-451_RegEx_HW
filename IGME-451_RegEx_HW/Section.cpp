#include "stdafx.h"
#include "Section.h"


Section::Section()
{
}


Section::~Section()
{
	for (std::map<std::string, DatumBase*>::iterator pairIter = pairs.begin(); pairIter != pairs.end(); ++pairIter) {
		delete(pairIter->second);
	}
	for (std::map<std::string, Section*>::iterator subIter = subsections.begin(); subIter != subsections.end(); ++subIter) {
		delete(subIter->second);
	}
}

std::map<std::string, DatumBase*> Section::getPairs()
{
	return pairs;
}

std::map<std::string, Section*> Section::getSubsections()
{
	return subsections;
}

void Section::addPair(std::string key, DatumBase* value)
{
	pairs[key] = value;
}

void Section::addPair(std::string subName, std::string key, DatumBase* value)
{
	std::map<std::string, Section*>::iterator subIter = subsections.find(subName);
	if (subIter != subsections.end()) {
		subIter->second->addPair(key, value);
	}
}

bool Section::addSubsection(std::string name)
{
	if (subsections.count(name)) {
		// Error: can't have multiple subsections w/ the same name.
		return false;
	}
	subsections[name] = new Section();
	return true;
}
