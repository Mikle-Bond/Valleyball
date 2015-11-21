#include "player.h"

void Player::set_block(void)
{
	a = this->get_pos();
	b = a + Vector2D(0.0, height_);
}

Player::Player(const Vector2D &left, const Vector2D &right, double height,
	double max_speed, double max_force, double curr) 
:
	
	Movable(left, right, (right - left) * curr, Vector2D(0.0, 0.0)),
	height_(height),
	max_force_(max_force),
	max_speed_(max_speed)
{
	set_block();
}

Player::~Player()
{

}

void Player::move(double dt)
{
	Movable::move(dt);
	set_block();
}

