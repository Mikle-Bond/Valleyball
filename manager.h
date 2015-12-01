#ifndef MANAGER_H
#define MANAGER_H 

#include <vector>
#include <string>
#include "vector2d.h"
#include "block.h"
#include "player.h"

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
 * This Player *is *loser.
 *
 * The special kind of Block is Net. There is no need for another 
 * class for it. The only differance is that Net 'belongs' to player,
 * who touched the Ball last.
 */

class Ball;

class Manager 
{
public:
	static Manager& getSingleton();
	// We should catch the objects, and not allow 
	// to the others to manage them outside,
	// not through the manager.
	// So, I think it is nice place for moving semantics.
	
	void addNet(Block *net);
	void addBlock(Block *blk, const std::string & obeyer);
	void addPlayer(Player *plr, const std::string & name);
	void addBall(Ball *bll);

	// Ok, here is the first big crutch:
	// The section with methods for two-players game!
	const Player * getAnotherPlayer(const Player * t);
	// To explain this functions, we need to understand game
	// as battle between *two* players. 
	// But the manager was written to manage *many* players. So, 
	// I need to make up this place, 'cos it's confusing.

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
	std::vector<block_t> block_tab;
	std::vector<ball_t> ball_tab;
	
	struct player_t {
		Player *plr;
		std::string name;
	};

	std::vector<player_t> player_tab;

	// Names
	Player * getPlayer(const std::string & str); // returns nullptr if not in name_tab
	
};

Manager * Manager::single = nullptr;

#endif // MANAGER_H 
