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

Movable::Movable(const Vector2D &left, const Vector2D &right, 
	double height, double position)
:
	lt_edge_(left),
	rt_edge_(right),
	pos_mul_(position)
{
	direction_ = right - left;
	direction_.normalize();
	a = (right - left) * position + left;
	b = a + Vector2D(0.0, height);

}

Vector2D Movable::get_pos(void)
{
	return a;
}

Vector2D Movable::get_head(void)
{
	return b;
}

void Movable::move_by(double meters)
{
	if (meters == 0.0) 
		return;
	Vector2D temp = direction_ * meters + get_pos();
	temp.x / 
}
