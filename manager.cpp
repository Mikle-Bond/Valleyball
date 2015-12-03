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

Player & Manager::addPlayer(const std::string & name, const std::string & type)
{
	auto it = factories.find(type);
	if (it == factories.end()) {
		throw; // Player realization is not registered.
	}
	auto y = player_tab.count(name);
	if (y > 0) {
		throw; // Player already exist.
	}
	Player * plr = it->second->create();
	player_tab.insert(std::make_pair(name, plr));
	return *plr;
}

const Player & Manager::getPlayer(const std::string & name) const
{
	return *(player_tab.at(name));
}

Block & Manager::addNet(const std::string & name)
{

	if (block_tab.count(name) > 0)
		throw; // Block already exist.
	Block *x = new Block();
	net_tab.insert(std::make_pair(name, x));
	return *x;
}


const Block & Manager::getNet(const std::string & name) const
{
	return *(net_tab.at(name));
}

Block & Manager::addBlock(const std::string & name, const std::string & obeyer)
{
	Player * res = player_tab.at(obeyer); // TODO: make custom exception
	Block * blk = new Block();
	if (block_tab.count(name) > 0)
		throw; // Block is already exist.
	block_t y;
	y.obj = blk;
	y.plr = res;
	block_tab.insert(std::make_pair(name, y));
	return *blk;
}
	
const Block & Manager::getBlock(const std::string & name) const
{
	return *(block_tab.at(name).obj);
}

Manager::ExitStatus Manager::nextFrame()
{
	// check for collisions of balls
	for (auto ball_iter = ball_tab.begin(); ball_iter != ball_tab.end(); ++ball_iter) {
		Ball * bll = ball_iter->second.obj;
		// ... with nets
	  	for (auto net_iter = net_tab.begin(); net_iter != net_tab.end(); ++net_iter) {
			Block * net = net_iter->second;
			if (bll->IsCrossing(*net)) {
				// (bll->second).plr is looser;
			}
		}	
		// ... with walls
	  	for (auto block_iter = block_tab.begin(); block_iter != block_tab.end(); ++block_iter) {
			Block * blk = (block_iter->second).obj;
			if (bll->IsCrossing(*blk)) {
				// (blk->second).plr is looser;
			}
		}
		// ... with players
	  	for (auto plr_iter = player_tab.begin(); plr_iter != player_tab.end(); ++plr_iter) {
			Player * plr = plr_iter->second;
			if (bll->IsCrossing(*plr)) {
				bll->push(plr->get_force(), dt_);
				// In the perfect world there should be the pointer to the ball, 
				// as a paraneter to .get_force(), but I'll do this later.
			}
			plr->idle();
			plr->move(dt_);
		}
		// ... with fouth dimention
		bll->move(dt_);
	} 

	return ExitStatus::OK;
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

