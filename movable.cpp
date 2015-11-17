#include "movable.h"


Movable::Movable(const Vector2D &left, const Vector2D &right, 
	const Vector2D &st_position, const Vector2D &st_speed)
:
	lt_edge_(left),
	rt_edge_(right),
	position_(st_position),
	speed(st_speed)
{

}

Vector2D Movable::get_pos(void)
{
	return position_;
}

void Movable::move(double dt)
{
	Vector2D offset = speed * dt;
	position_ += offset;
}

Movable::~Movable() {}


