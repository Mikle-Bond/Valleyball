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
	
	int res = name_tab.size(); 
	name_t x;
	x.name = name; 
	x.val = res;
	name_tab.push_back(std::move(x));
	
	return res;
}

void Manager::addNet(Block *net)
{
	net_tab.push_back(net);
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
	int res = get_num(obeyer);
	block_t y;
	y.blk = blk;
	y.owner = res;
	player_tab.push_back(std::move(y));
}
	
void addBall(Ball *bll)
{
	ball_t y;
	y.bll = bll;
	y.last = 0;
	ball_tab.push_back(std::move(y));
}



