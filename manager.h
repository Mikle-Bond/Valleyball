﻿#ifndef MANAGER_H
#define MANAGER_H 

#include <map>
#include <string>
#include "vector2d.h"
#include "ball.h"
#include "block.h"
#include "player.h"
#include "factory.h"

/* Ok. Manager can manage. After giving him the beginning configuration
 * we can change nothing. So, The basic usage is to place needed objects
 * to manager an recount them with according method. 
 *
 * Objects in Manager are divided to three groups.
 *
 * Blocks are non-moovable statc plates. All we have to know about it,
 * is what to do, if the Ball cross one of them. To simplify the task,
 * we remember, what player 'obey' this block.
 *
 * Players are the moovable blocks. They have their own logic, so 
 * manager doesn't care for their behavior.
 *
 * Balls are spacial moovable objects, with their own 'phisical' 
 * behavior. Also we need to know, who wf Players touched the Ball last.
 *
 * To catch the end of the game, we are looking for collisions of ball
 * and block, and if we found it, we are looking to who obey this block.
 * This Player *is* loser.
 *
 * The special kind of Block is Net. There is no need for another 
 * class for it. The only differance is that Net 'belongs' to player,
 * who touched the Ball last.
 */

class Ball;

struct ITimer 
{
	explicit ITimer(double dt = 0.0);
	void setStep(double new_dt);
	double getStep() const;
private:
	double dt_;
};

class Manager : private Factory
{
public:
	static Manager& getSingleton();
	static bool resetSingleton();
	// We should catch the objects, and not allow 
	// to the others to manage them outside,
	// not through the manager.
	
	enum class Status { 
		OK, 			// stands for no special state
		ATTACK, 		// one or more players touched the ball
		GAME_OVER, 		// ball contacted with surface
		NOT_STARTED, 		// manager is ready to begin
	       	DESTROYED		// manager is seted down
	};
	struct State {
		Status currentStatus = Status::DESTROYED;
		const std::string * playerName = nullptr;
		const std::string * ballName = nullptr;
		const std::string * blockName = nullptr;
	};

	// Nets
	Block & addNet(const std::string & name);
	const Block & getNet(const std::string & name) const;
	// Blocks
	Block & addBlock(const std::string & name, const std::string & obeyer);
	const Block & getBlock(const std::string & name) const;
	// Players
	Player & addPlayer(const std::string & name, const std::string & type);
	const Player & getPlayer(const std::string & name) const;
	// Balls
	Ball & addBall(const std::string & name);
	const Ball & getBall(const std::string & name) const;

	static const State & getState();

	Status nextFrame(void);

	const ITimer * getTimer() const;
	ITimer * getTimer();
	void setStep(double new_dt);
	double getStep() const;

private:
	Manager();
	Manager(const Manager &);	
	~Manager();

	// Used fo correct end of game.
	const std::string * getLoserName(const Player * plr) const;
	void setState(
		const Status sts,
		const std::string * plr_name, 
		const std::string * bll_name, 
		const std::string * blk_name);

	static Manager * single;

	static State state_;

	ITimer timer_;

	// Here ve have a list for each kind of objects.
	// To ease handling them, we can put them into
	// container like this.
	template <class T>
	struct list_elem_t {
		T *obj;   	// Object of scene,
		Player *plr;	// and the owner player.
	};

	typedef list_elem_t<Block> block_t;
	typedef list_elem_t<Ball> ball_t;

	// As was mentioned, we need "nets".
	// But we will handle them as all others Blocks,
	// marking them as owned by (nullptr)
	
	struct player_t {
		Player *plr;
		std::string name;
	};

	// Each element has its identifier, whitch is a name of element.
	std::map<std::string, Player *> player_tab;
	std::map<std::string, Block *> net_tab;
	std::map<std::string, ball_t> ball_tab;
	std::map<std::string, block_t> block_tab;
};

#endif // MANAGER_H 
