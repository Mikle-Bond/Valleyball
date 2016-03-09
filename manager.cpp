#include "manager.h"
#include <stdexcept>

using std::logic_error;

Manager * Manager::single = nullptr;
Manager::State Manager::state_;

namespace {

class ManagerDestroyer 
{
public:
	ManagerDestroyer() {}
	~ManagerDestroyer() { Manager::resetSingleton(); }
};
static ManagerDestroyer ManagerDestroyerClass;

} // namespace


ITimer::ITimer(double dt)
{
	if (dt < 0.0) {
		throw std::invalid_argument("Timer step can not be negative");	
	} else {
		dt_ = dt;
	}
}

void ITimer::setStep(double new_dt)
{
	if (new_dt >= 0.0)
		dt_ = new_dt;
}

double ITimer::getStep() const
{
	return dt_;
}

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
		throw logic_error("Player realization is not registered: " + type);
	}

	Player * plr = it->second->create();
	player_tab.addEntry(name, plr);
	return *plr;
}

const Player & Manager::getPlayer(const std::string & name) const
{
	return *(player_tab.getObject(name));
}

Net & Manager::addNet(const std::string & name)
{
	Net *x = new Net();
	net_tab.addEntry(name, x, nullptr);
	return *x;
}

const Net & Manager::getNet(const std::string & name) const
{
	return *(net_tab.getObject(name));
}

Block & Manager::addBlock(const std::string & name, const std::string & obeyer)
{
	Player * res = player_tab.getObject(obeyer);
	Block * blk = new Block();
	block_tab.addEntry(name, blk, res);
	return *blk;
}
	
const Block & Manager::getBlock(const std::string & name) const
{
	return *(block_tab.getObject(name));
}

Ball & Manager::addBall(const std::string & name)
{
	Ball * bll = new Ball();
	ball_tab.addEntry(name, bll, nullptr);
	return *bll;
}

const Ball & Manager::getBall(const std::string & name) const
{
	return *(ball_tab.getObject(name));
}

template<typename T>
Manager::Status Manager::collideBalls(ObjectTable<T> & colliders)
{
	for (auto ball_iter = ball_tab.begin(); ball_iter != ball_tab.end(); ++ball_iter) {
		const Ball * bll = ball_iter->second.object;
	  	for (auto iter = colliders.begin(); iter != colliders.end(); ++iter) {
			const Block * net = static_cast<const Block *>((iter->second).object);
			if (bll->IsCrossing(*net)) {
				setState(
					Status::GAME_OVER,
					player_tab.findName((ball_iter->second).owner),
					&(ball_iter->first),
					&(iter->first));
				return state_.currentStatus;
			}
		}
	}
	return state_.currentStatus;
}

template<>
Manager::Status Manager::collideBalls(ObjectTable<Player> & colliders)
{
	for (auto ball_iter = ball_tab.begin(); ball_iter != ball_tab.end(); ++ball_iter) {
		Ball * bll = ball_iter->second.object;
	  	for (auto plr_iter = colliders.begin(); plr_iter != colliders.end(); ++plr_iter) {
			Player * plr = plr_iter->second;
			if (bll->IsCrossing(*plr)) {
				bll->push(plr->get_force());
				// In the perfect world there should be the pointer to the ball, 
				// as a paraneter to .get_force(), but I'll do this later.
				setState(
					Status::ATTACK,
					&(plr_iter->first),
					&(ball_iter->first),
					nullptr);
				ball_iter->second.owner = plr;
				// notice that here is no return.
			}
		}
	}
	return state_.currentStatus;
}


Manager::Status Manager::nextFrame()
{
	if (state_.currentStatus == Status::GAME_OVER)
		return Status::GAME_OVER;
	state_.currentStatus = Status::OK;

	// check for collisions of balls
	// ... with nets
	if (collideBalls(net_tab) == Status::GAME_OVER)
		return Status::GAME_OVER;
	// ... with walls
	if (collideBalls(block_tab) == Status::GAME_OVER)
		return Status::GAME_OVER;
	// ... with players
	collideBalls(player_tab);

	// ... with fourth dimention
	for (auto ball_iter = ball_tab.begin(); ball_iter != ball_tab.end(); ++ball_iter) {
		Ball * bll = ball_iter->second.object;
		bll->move();
		// bll->draw();
	} 

	// same for players
	for (auto plr_iter = player_tab.begin(); plr_iter != player_tab.end(); ++plr_iter) {
		Player * plr = plr_iter->second;
		plr->idle();
		plr->move();
//		plr->draw();
	}
//	for (auto net_iter = net_tab.begin(); net_iter != net_tab.end(); ++net_iter) {
//		net_iter->second->draw();
//	}
//	for (auto block_iter = block_tab.begin(); block_iter != block_tab.end(); ++block_iter) {
//		(block_iter->second).obj->draw();
//	}

	return state_.currentStatus;
}

const ITimer * Manager::getTimer() const
{
	return &timer_;
}

ITimer * Manager::getTimer()
{
	return &timer_;
}

// For the backward capability, this functions are forwarding ITimer interface
void Manager::setStep(double new_dt)
{
	timer_.setStep(new_dt);
}

double Manager::getStep() const
{
	return timer_.getStep();
}

void Manager::setState(
	const Manager::Status sts,
	const std::string * plr_name, 
	const std::string * bll_name, 
	const std::string * blk_name)
{
	state_.currentStatus = sts;
	state_.playerName = plr_name;
	state_.ballName = bll_name;
	state_.blockName = blk_name;
}

const Manager::State & Manager::getState()
{
	return state_;
}

Manager::~Manager()
{
	state_.currentStatus = Status::DESTROYED;
}

