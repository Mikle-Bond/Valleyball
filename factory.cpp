#include "factory.h"

void Factory::registerType(const std::string & type, PlayerFactory * handler)
{
	factories[type] = handler;
}

Factory::Factory()
{

}


