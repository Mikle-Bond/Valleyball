#include "manager.h"

Manager& Manager::getSingleton()
{
	static Manager single;
	return single;
}

int Manager::get_num(const std::string & str)
{
	for (auto it = name_tab.begin(); it != name_tab.end(); ++it) {
		if ((*it).name == str) {
			return (*it).val;
		}
	}
	return -1;
}




