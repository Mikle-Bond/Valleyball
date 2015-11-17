#include "player.h"

Player::Player(const Vector2D &left, const Vector2D &right, double height, 
	double max_speed, double max_force, double curr) 
:
	Movable(left, right, height, curr),
	max_force_(max_force),
	max_speed_(max_speed)
{

}

Player::~Player()
{

}

