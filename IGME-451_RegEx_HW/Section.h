#pragma once

#include<string>
#include<map>
#include<list>
#include "DatumBase.h"
#include "Datum.h"
#include "DatumList.h"

#define ENTRY std::pair<std::string, DatumBase*>

class Section
{
public:
	//constructors
	///<summary>Constructor for the Section object.</summary>
	Section();
	
	///<summary>Constructor for the Section object.</summary>
	///<param name="name">The name/key for the section.</param>
	Section(std::string name);

	///<summary>Deconstructs a deleted Section object.</summary>
	~Section();

	//getters
	///<summary>Gets the name (key) of the Section object.</summary>
	///<returns>The name as a std::string.</returns>
	std::string getName();

	///<summary>Gets a list of the entries for this section.</summary>
	///<returns>A list that contains the entities, or an empty list if there are no entities.</returns>
	std::list<ENTRY> getEntries();
	
	///<summary>Gets a list of the entries for a subsection of this section.</summary>
	///<param name="subsection">The name of the containing subsection.</param>
	///<returns>A list that contains the entities, or an empty list if there are no entities or the subsection doesn't exist.</returns>
	std::list<ENTRY> getEntries(std::string subsection);

	///<summary>Gets an entry in this section</summary>
	///<param name="key">The key for the entry.</param>
	///<returns>The entry as a pair object, or a default pair if the entry doesn't exist.</returns>
	ENTRY getEntry(std::string key);

	///<summary>Gets an entry in a given subsection</summary>
	///<param name="subsection">The name of the containing subsection.</param>
	///<param name="key">The key for the entry.</param>
	///<returns>The entry as a pair object, or a default pair if the entry or subsection doesn't exist.</returns>
	ENTRY getEntry(std::string subsection,std::string key);
	
	///<summary>Gets the list of the subsections for this section.</summary>
	///<returns>A list that contains pointers to the retrieved subsections, or an empty list if there are no subsections.</returns>
	std::list<Section*> getSubsections();

	///<summary>Gets the subsection  with the given name.</summary>
	///<param name="name">The name of the subsection to seach for.</param>
	///<returns>A pointer to the named subsection, or a nullpointer if it doesn't exist.<returns>
	Section* getSubsection(std::string subName);

	//adding functions
	///<summary>Adds a new key-value pair to the section. (Over-writting values with the same key.)</summary>
	///<param name="key">The key used to store the value.</param>
	///<param name="value">The given value.</param>
	void addPair(std::string key, DatumBase* value);


	///<summary>Adds a new key-value pair to a given subsection. (Over-writting values with the same key.)</summary>
	///<param name="subsection">The subsection to store the data in.</param>
	///<param name="key">The key used to store the value.</param>
	///<param name="value">The given value.</param>
	void addPair(std::string subsection,std::string key, DatumBase* value);

	///<summary>Adds a subsection to this section.</summary>
	///<param name="subsection">The subsection to be added.</param>
	///<returns>True if the subsection was successfully added, false if there was an error 
	///(such as the subsection already exists).</returns>
	bool addSubsection(std::string subName);

	//other
	void print(std::ostream& out);
private:
	//fields
	std::string name;
	std::map<std::string, DatumBase*> pairs;
	std::map<std::string, Section*> subsections;
};

