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
	void addBlock(Block *blk, std::string obeyer);
	void addPlayer(Player *plr, std::string name);
	void addBall(Ball *bll);
private:
	Manager();
	Manager(const Manager &);	
	
	struct name_t {
		std::string name;
		int val;
	};
	struct block_t {
		int owner;
		Block *blk;
	};
	struct ball_t {
		int last;
		Ball *bll;
	};
	struct player_t {
		int val;
		Player *plr;
	};

	std::vector<name_t> name_tab;
	std::vector<block_t> block_tab;
	std::vector<ball_t> ball_tab;
	std::vector<player_t> player_tab;
	std::vector<Block *> net_tab;

	// Names
	int get_num(const std::string & str); // returns -1 if not in name_tab
	
};

#endif // MANAGER_H 
