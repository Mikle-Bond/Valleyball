#ifndef FACTORY_H
#define FACTORY_H

/* Factory method for Player's derived classes.
 *
 * Usage:
 * There is no need to include this file separately in the 
 * Player's derived header -- it's already done in "player.h".
 * To use class in Manager, write in the .cpp file something
 * like: 
 * 	REGISTRATE_PLAYER(MyPlayer);
 * and feel free to use this player in Manager.
 */

#include <map>

class Player;

class PlayerFactory
{
public:
	virtual Player * create() = 0;
};


class Factory 
{
public:
	static void registerType(const std::string & type, PlayerFactory * handler);
protected:
	Factory();
	typedef std::map<std::string, PlayerFactory *> FactMap;
	static FactMap & factories; 		// just a shortcut
protected:
	static FactMap & factoriesContainer();	// contain static object
};

// Purpose to use define-macro instead of template 
// registration class is the name of class. To have the 
// opportunity to create class by it's name we need to 
// parse the name as quoted string during precompilation.
#define PEGISTRATE_PLAYER(name)					\
class name##Factory : public PlayerFactory			\
{								\
	Player * create() {					\
		return new name();				\
	}							\
	name##Factory() {					\
		Factory::registerType(#name, this);		\
	}							\
};								\
static name##Factory name##Registrator

#endif // FACTORY_H

