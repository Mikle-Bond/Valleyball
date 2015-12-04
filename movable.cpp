#include "movable.h"


Movable::Movable(const Vector2D &left, const Vector2D &right, 
	const Vector2D &st_position, const Vector2D &st_speed)
:
	speed(st_speed),
	position_(st_position),
	lb_edge_(left),
	rt_edge_(right)
{

}

Vector2D Movable::get_pos(void) const
{
	return position_;
}

void Movable::move(double dt)
{
	Vector2D offset = speed * dt;
	position_ += offset;
	if (position_.x < lb_edge_.x)
		position_.x = lb_edge_.x;
	if (position_.y < lb_edge_.y)
		position_.y = lb_edge_.y;
	if (position_.x > rt_edge_.x)
		position_.x = rt_edge_.x;
	if (position_.y > rt_edge_.y)
		position_.y = rt_edge_.y;
}
	
void Movable::initMovable(const Vector2D & left, const Vector2D & right, 
	const Vector2D & position, const Vector2D & st_speed)
{
	lb_edge_ = left;
	rt_edge_ = right;
	position_ = position;
	speed = st_speed;
}

Movable::~Movable() {}


