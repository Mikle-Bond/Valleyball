#include "manager.h"

Manager * Manager::single = nullptr;
Manager::State Manager::state_;

namespace {

template <typename T>
inline void killMap(std::map<std::string, T> & mp)
{
	for (auto i = mp.begin(); i != mp.end(); ++i) {
		delete (i->second).obj;
	}
}

class ManagerDestroyer 
{
public:
	ManagerDestroyer() {}
	~ManagerDestroyer() { Manager::resetSingleton(); }
};
static ManagerDestroyer ManagerDestroyerClass;

} // namespace

Manager::Manager()
{
	state_.currentStatus = Status::NOT_STARTED;
}

Manager& Manager::getSingleton()
{
	if (!single)
		single = new Manager();
	return *single;
}

bool Manager::resetSingleton()
{
	if (single) {
		delete single;
		single = nullptr;
		return true;
	}
	return false;
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

Ball & Manager::addBall(const std::string & name)
{
	if (ball_tab.count(name) > 0)
		throw; // Ball is already exist.
	Ball * bll = new Ball();
	ball_t y;
	y.plr = nullptr;
	y.obj = bll;
	ball_tab.insert(std::make_pair(name, y));
	return *bll;
}

const Ball & Manager::getBall(const std::string & name) const
{
	return *(ball_tab.at(name).obj);
}

Manager::Status Manager::nextFrame()
{
	if (state_.currentStatus == Status::GAME_OVER)
		return Status::GAME_OVER;
	state_.currentStatus = Status::OK;

	// check for collisions of balls
	for (auto ball_iter = ball_tab.begin(); ball_iter != ball_tab.end(); ++ball_iter) {
		Ball * bll = ball_iter->second.obj;
		// ... with nets
	  	for (auto net_iter = net_tab.begin(); net_iter != net_tab.end(); ++net_iter) {
			Block * net = net_iter->second;
			if (bll->IsCrossing(*net)) {
				state_.currentStatus = Status::GAME_OVER;
				state_.playerName = getLoserName((ball_iter->second).plr);
				state_.ballName = &(ball_iter->first);
				state_.blockName = &(net_iter->first);
				return Status::GAME_OVER;
			}
		}
		// ... with walls
	  	for (auto block_iter = block_tab.begin(); block_iter != block_tab.end(); ++block_iter) {
			Block * blk = (block_iter->second).obj;
			if (bll->IsCrossing(*blk)) {
				state_.currentStatus = Status::GAME_OVER;
				state_.playerName = getLoserName((block_iter->second).plr);
				state_.ballName = &(ball_iter->first);
				state_.blockName = &(block_iter->first);
				return Status::GAME_OVER;
			}
		}
		// ... with players
	  	for (auto plr_iter = player_tab.begin(); plr_iter != player_tab.end(); ++plr_iter) {
			Player * plr = plr_iter->second;
			if (bll->IsCrossing(*plr)) {
				bll->push(plr->get_force(), dt_);
				// In the perfect world there should be the pointer to the ball, 
				// as a paraneter to .get_force(), but I'll do this later.
				state_.currentStatus = Status::ATTACK;
				state_.ballName = &(ball_iter->first);
				state_.playerName = &(plr_iter->first);
				state_.blockName = nullptr;
				ball_iter->second.plr = plr;
				// notice that here is no return.
			}
		}
		// ... with fouth dimention
		bll->move(dt_);
		// bll->draw();
	} 

	for (auto plr_iter = player_tab.begin(); plr_iter != player_tab.end(); ++plr_iter) {
		Player * plr = plr_iter->second;
		plr->idle();
		plr->move(dt_);
		plr->draw();
	}
	for (auto net_iter = net_tab.begin(); net_iter != net_tab.end(); ++net_iter) {
		net_iter->second->draw();
	}
	for (auto block_iter = block_tab.begin(); block_iter != block_tab.end(); ++block_iter) {
		(block_iter->second).obj->draw();
	}

	return state_.currentStatus;
}

void Manager::setStep(double new_dt)
{
	if (new_dt >= 0.0)
		dt_ = new_dt;
}

double Manager::getStep() const
{
	return dt_;
}

const Manager::State & Manager::getState()
{
	return state_;
}

const std::string * Manager::getLoserName(const Player * plr) const
{
	for (auto it = player_tab.begin(); it != player_tab.end(); ++it) {
		if (plr == it->second)
			return &(it->first);
	}
	return nullptr;
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
	state_.currentStatus = Status::DESTROYED;
}

