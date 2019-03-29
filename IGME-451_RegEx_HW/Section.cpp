#include "stdafx.h"
#include "Section.h"


Section::Section()
{
	pairs = new std::map<std::string, Datum>();
	subsections = new std::map<std::string, Section>();
}


Section::~Section()
{
	if (pairs != nullptr) {
		delete pairs;
		pairs = nullptr;
	}
	if (subsections != nullptr) {
		delete subsections;
		subsections = nullptr;
	}
}

std::map<std::string, Datum>* Section::getPairs()
{
	return pairs;
}

std::map<std::string, Section>* Section::getSubsections()
{
	return subsections;
}

void Section::addPair(std::string key, Datum value)
{
	(*pairs)[key] = value;
}

void Section::addPair(std::string subName, std::string key, Datum value)
{
	std::map<std::string, Section>::iterator subIter = subsections->find(subName);
	if (subIter != subsections->end()) {
		subIter->second.addPair(key, value);
	}
}

bool Section::addSubsection(std::string name)
{
	if (!subsections->empty() && subsections->count(name)) {
		// Error: can't have multiple subsections w/ the same name.
		return false;
	}
	(*subsections)[name] = Section();
	return true;
}
