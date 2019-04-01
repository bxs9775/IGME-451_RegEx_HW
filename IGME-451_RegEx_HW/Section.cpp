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
	Section* subPtr = getSubsection(subsection);
	if (!subPtr) {
		return std::list<ENTRY>();
	}
	return subPtr->getEntries();
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
	Section* subPtr = getSubsection(subsection);
	if (!subPtr) {
		return ENTRY();
	}
	return subPtr->getEntry(key);
}


std::list<Section*> Section::getSubsections()
{
	std::list<Section*> sections;
	for (std::map<std::string,Section*>::iterator iter = subsections.begin(); iter != subsections.end(); ++iter) {
		sections.push_back(iter->second);
	}
	return sections;
}

Section * Section::getSubsection(std::string subName)
{
	std::map<std::string,Section*>::iterator sectionIter = subsections.find(subName);
	if (sectionIter == subsections.end()) {
		return nullptr;
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

bool Section::addSubsection(std::string subName)
{
	if (subsections.count(subName)) {
		// Error: can't have multiple subsections w/ the same name.
		return false;
	}
	subsections[subName] = new Section(subName);
	return true;
}

void Section::print(std::ostream & out)
{
	out << "[" << getName() << "]" << std::endl;
	std::list<ENTRY> entries = getEntries();
	for (std::list<ENTRY>::iterator pairIter = entries.begin(); pairIter != entries.end(); ++pairIter) {
		DatumBase* value = pairIter->second;
		
		if (value->getVarType() == ConfigVar::configVar::CONFIG_LIST_T) {
			((DatumList*)value)->print(out);
		}
		else {
			((Datum*)value)->print(out);
		}
	}

	std::list<Section*> secs = getSubsections();
	for (std::list<Section*>::iterator secIter = secs.begin(); secIter != secs.end(); ++secIter) {
		out << "Subsection: ";
		(*secIter)->print(out);
		out << std::endl;
	}
}
