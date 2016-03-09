#ifndef OBJECTTABLE_H
#define OBJECTTABLE_H 

#include <map>
#include <string>
#include <stdexcept>
#include "player.h"

template <typename T>
class ObjectTable
{
public:
	struct ObjectEntry
	{
		T * object;
		Player * owner;	
	};

	ObjectTable() = default;

	~ObjectTable() {
		for (auto it : table_) {
			delete it.second.object;
		}
	}

	T * addEntry(std::string name, T * object, Player * owner) {
		int num = table_.count(name); // check for repeats
		if (num > 0) 
			throw std::logic_error("Object with the name '" + name + "' is already added.");
		ObjectEntry temp = { object, owner };
		table_.insert(std::make_pair(name, temp));
		return object;
	}

	T * getObject(const std::string & name) const {
		int num = table_.count(name);
		if (num == 0) 
			throw std::logic_error("No entry for the '" + name + "'");
		return table_.at(name).object;
	}
	
	Player * getOwner(const std::string & name) const {
		int num = table_.count(name);
		if (num == 0) 
			throw std::logic_error("No entry for the '" + name + "'");
		return table_.at(name).owner;
	}

	decltype(auto) begin() {
		return table_.begin();
	}

	decltype(auto) end() {
		return table_.end();
	}

private:
	std::map<std::string, ObjectEntry> table_;
};

template <>
class ObjectTable<Player>
{
	std::map<std::string, Player*> table_;
public:
	ObjectTable() = default;

	~ObjectTable() {
		for (auto it : table_) {
			delete it.second;
		}
	}

	Player * addEntry(std::string name, Player * object) {
		int num = table_.count(name); // check for repeats
		if (num > 0) 
			throw std::logic_error("Object with the name '" + name + "' is already added.");
		table_.insert(std::make_pair(name, object));
		return object;
	}

	Player * getObject(const std::string & name) const {
		int num = table_.count(name);
		if (num == 0) 
			throw std::logic_error("No entry for the '" + name + "'");
		return table_.at(name);
	}

	const std::string * findName(Player * ptr) {
		for (auto it = table_.begin(); it != table_.end(); ++it) {
			if (ptr == it->second)
				return &(it->first);
		}
		return nullptr;
		
	}
	
	decltype(auto) begin() {
		return table_.begin();
	}

	decltype(auto) end() {
		return table_.end();
	}
};

#endif // OBJECTTABLE_H
