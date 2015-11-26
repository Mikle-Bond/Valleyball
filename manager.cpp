#include "manager.h"

namespace {

template <typename T>
inline void killVector(std::vector<T> & vect)
{
	for (auto i = vect.begin(); i != vect.end(); ++i) {
		delete i->obj;
	}
}

}

Manager& Manager::getSingleton()
{
	static Manager single;
	return single;
}

Player * Manager::getPlayer(const std::string & str)
{
	for (auto it = player_tab.begin(); it != player_tab.end(); ++it) {
		if ((*it).name == str) {
			return (*it).plr;
		}
	}
	
	return nullptr;
}

void Manager::addNet(Block *net)
{
	block_t x;
	x.plr = nullptr;
	x.obj = net;
	block_tab.push_back(std::move(x));
}


void Manager::addPlayer(Player *plr, const std::string & name)
{
	int res = get_num(name);
	player_t y;
	y.plr = plr;
	y.val = res;
	player_tab.push_back(std::move(y));
}

void Manager::addBlock(Block *blk, const std::string & obeyer)
{
	Player * res = get_num(obeyer);
	if (!res || !blk) { throw; }
	block_t y;
	y.obj = blk;
	y.plr = res;
	player_tab.push_back(std::move(y));
}
	
void addBall(Ball *bll)
{
	if (!bll) { throw; }
	ball_t y;
	y.obj = bll;
	y.plr = nullptr;
	ball_tab.push_back(std::move(y));
}

const Player * getAnotherPlayer(const Player * t)
{
	for (auto i = player_tab.begin(); i != player_tab.end(); ++i) {
		if (i->plr != t)
			return i->plr;
	}
	return nullptr;
}


Manager::~Manager()
{
	// Nets and blocks
	killVector<block_t>(block_tab);
	// Balls
	killVector<ball_t>(ball_tab);
	// Players
	for (auto i = player_tab.bagin(); i != player_tab.end(); ++i) {
		delete i->plr;
	}
}

