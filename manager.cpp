#include "manager.h"

namespace {

template <typename T>
inline void killMap(std::map<std::string, T> & mp)
{
	for (auto i = mp.begin(); i != mp.end(); ++i) {
		delete (i->second).obj;
	}
}

} // namespace

Manager& Manager::getSingleton()
{
	if (!single)
		single = new Manager();
	return *single;
}

#if 0
template <class T>
T & Manager::addPlayer(const std::string & name)
{
//	auto it = factories.find(type);
//	if (it->first != type) {
//		throw; // Player realization is not registered.
//	}
	
	auto y = player_tab.find(name);
	if (y->first == name) {
		throw; // Player already exist.
	}
	T * plr = new T(); // = it->second->create();
	player_tab.insert(std::make_pair(name, static_cast<Player*>(plr)));
	return *plr;
}
#endif // 0

const Player & Manager::getPlayer(const std::string & name)
{
	return *(player_tab.at(name));
}

Block & Manager::addNet(const std::string & name)
{

	auto it = block_tab.find(name);
	if (it->first == name)
		throw; // Block already exist.
/*
	auto y = 
		throw; // No such player.
*/		
	Block *x = new Block();
	net_tab.insert(std::make_pair(name, x));
	return *x;
}


const Block & Manager::getNet(const std::string & name)
{
	return *(net_tab.at(name));
}

Block & Manager::addBlock(const std::string & name, const std::string & obeyer)
{
	Player * res = player_tab.at(obeyer);
	Block * blk = new Block();
//	if (!res || !blk) { throw; }
	if (block_tab.find(name)->first == name)
		throw; // Block is already exist.
	block_t y;
	y.obj = blk;
	y.plr = res;
	block_tab.insert(std::make_pair(name, y));
	return *blk;
}
	
const Block & Manager::getBlock(const std::string & name)
{
//	if (!bll) { throw; }
	return *(block_tab.at(name).obj);
}

Manager::~Manager()
{
	// Blocks
	killMap<block_t>(block_tab);
	// Balls
	killMap<ball_t>(ball_tab);
	// Players
	for (auto i = player_tab.begin(); i != player_tab.end(); ++i) {
		delete i->second;
	}
	// Nets
	for (auto i = net_tab.begin(); i != net_tab.end(); ++i) {
		delete i->second;
	}
}

