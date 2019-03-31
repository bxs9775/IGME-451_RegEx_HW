#include "stdafx.h"
#include "Section.h"


Section::Section():Section("")
{
}

Section::Section(std::string name)
{
	this->name = name;
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

std::string Section::getName()
{
	return name;
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

ENTRY Section::getEntry(std::string key)
{
	std::map<std::string, DatumBase*>::iterator pairIter = pairs.find(key);
	if (pairIter == pairs.end()) {
		return ENTRY();
	}
	DatumBase* value = pairIter->second;
	return ENTRY(key,value);
}

ENTRY Section::getEntry(std::string subsection, std::string key)
{
	return getSubsection(subsection)->getEntry(key);
}


std::list<Section*> Section::getSubsections()
{
	std::list<Section*> sections;
	for (std::map<std::string,Section*>::iterator iter = subsections.begin(); iter != subsections.end(); ++iter) {
		sections.push_back(iter->second);
	}
	return sections;
}

Section * Section::getSubsection(std::string subsection)
{
	std::map<std::string,Section*>::iterator sectionIter = subsections.find(subsection);
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

bool Section::addSubsection(std::string subsection)
{
	if (subsections.count(subsection)) {
		// Error: can't have multiple subsections w/ the same name.
		return false;
	}
	subsections[subsection] = new Section(subsection);
	return true;
}

std::string Section::toString()
{
	std::string strValue = getName();
	strValue.resize(MAX_STRING);

	strValue.append("\n");
	for (std::map<std::string, DatumBase*>::iterator pairIter = pairs.begin(); pairIter != pairs.end(); ++pairIter) {
		strValue.append(pairIter->second->toString());
	}
	for (std::map<std::string, Section*>::iterator subIter = subsections.begin(); subIter != subsections.end(); ++subIter) {
		strValue.append("Subsection: ");
		strValue.append(subIter->second->toString());
	}
	return strValue;
}
