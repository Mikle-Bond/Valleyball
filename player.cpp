#include "player.h"

Player::Player(Vector2D &left, Vector2D &right, double height, 
	double max_speed, double max_force, double curr) 
:
	pos(left, right, height, curr),
	max_force_(max_force),
	max_speed_(max_speed)
{

}

Player::~Player()
{

}

Player::position::position(Vector2D &left, Vector2D &right, 
	double height, double position)
:
	lt_edge_(left),
	rt_edge_(right),
	height_(height),
	pos_mul_(position)
{

}

Vector2D Player::position::get_pos()
{
	return (rt_edge_ - lt_edge_) * pos_mul_ + lt_edge_;
}

Vector2D Player::position::get_head()
{
	return get_pos() + Vector2D(0.0, height_);
}
