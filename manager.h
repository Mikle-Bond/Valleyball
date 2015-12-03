#ifndef MANAGER_H
#define MANAGER_H 

#include <map>
#include <string>
#include "vector2d.h"
#include "ball.h"
#include "block.h"
#include "player.h"
// #include "factory.h"

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

class Manager // : private Factory 
{
public:
	static Manager& getSingleton();
	// We should catch the objects, and not allow 
	// to the others to manage them outside,
	// not through the manager.
	
	// Nets
	Block & addNet(const std::string & name);
	const Block & getNet(const std::string & name);
	// Blocks
	Block & addBlock(const std::string & name, const std::string & obeyer);
	const Block & getBlock(const std::string & name);
	// Players
	template <class T>
	T & addPlayer(const std::string & name,
		const Vector2D &left, const Vector2D &right, double height,
		double max_speed, double max_force, double curr = 0.5);
	const Player & getPlayer(const std::string & name);
	// Balls
	Ball & addBall(const std::string & name);
	const Ball & getBall(const std::string & name);

private:
	Manager();
	Manager(const Manager &);	
	~Manager();

	static Manager * single;


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

Manager * Manager::single = nullptr;

template <class T>
T & Manager::addPlayer(const std::string & name,
	const Vector2D &left, const Vector2D &right, double height,
	double max_speed, double max_force, double curr)
{
	auto y = player_tab.find(name);
	if (y->first == name) {
		throw; // Player already exist.
	}
	T * plr = new T(left, right, height, max_speed, max_force, curr);
	player_tab.insert(std::make_pair(name, static_cast<Player*>(plr)));
	return *plr;
}

#endif // MANAGER_H 
