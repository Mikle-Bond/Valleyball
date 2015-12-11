#include "factory.h"

void Factory::registerType(const std::string & type, PlayerFactory * handler)
{
	static FactMap & fact_sc = factoriesContainer(); // another shortcut
	// just becouse tha 'main' referance still can be not inited.
	fact_sc[type] = handler;
}

// Here is a solution for 'static inordered initialization' problem.
// 
// 'factories' is a static object, which is used before main() to 
// collect information about th players. This task will be done
// in the beginning by anothet static objects, that will do the job
// in their construstors. And here is a problem.
// We don't know the order of their creation, so there is a huge 
// chance to meet UB.
// To avoid this, we will hide the 'factories' inside this method,
// and leave for the others only reference to this object.
// BTW, this shortcut is needed to avoid extra function call.
Factory::FactMap & Factory::factoriesContainer()
{
	static FactMap single_factory;
	return single_factory;
}

// Initialithing the shortcut.  
Factory::FactMap & Factory::factories = Factory::factoriesContainer();

Factory::Factory()
{

}


