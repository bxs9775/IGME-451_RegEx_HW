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

std::list<ENTRY> Section::getEntries()
{
	std::list<ENTRY> entries = std::list<ENTRY>();

	for (std::map<std::string, DatumBase*>::iterator iter = pairs.begin(); iter != pairs.end(); ++iter) {
		std::string key = iter->first;
		DatumBase* value = iter->second;
		entries.push_back(ENTRY(key,value));
	}
	return entries;
}

std::list<ENTRY> Section::getEntries(std::string subsection)
{
	return getSubsection(subsection)->getEntries();
}

ENTRY Section::getEntry(std::string name)
{
	std::map<std::string, DatumBase*>::iterator pairIter = pairs.find(name);
	if (pairIter == pairs.end()) {
		return ENTRY();
	}
	std::string key = pairIter->first;
	DatumBase* value = pairIter->second;
	return ENTRY(key,value);
}

ENTRY Section::getEntry(std::string subsection, std::string name)
{
	return getSubsection(subsection)->getEntry(name);
}


std::list<Section*> Section::getSubsections()
{
	std::list<Section*> sections;
	for (std::map<std::string,Section*>::iterator iter = subsections.begin(); iter != subsections.end(); ++iter) {
		sections.push_back(iter->second);
	}
	return sections;
}

Section * Section::getSubsection(std::string name)
{
	std::map<std::string,Section*>::iterator sectionIter = subsections.find(name);
	if (sectionIter == subsections.end()) {
		return new Section();
	}
	return sectionIter->second;
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
