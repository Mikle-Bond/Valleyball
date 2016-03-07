#include "movable.h"
#include "manager.h"


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

bool Movable::move()
{
    Vector2D old_pos = position_;
    Vector2D offset = speed * Manager::getSingleton().getStep();
	position_ += offset;
	if (position_.x < lb_edge_.x)
		position_.x = lb_edge_.x;
	if (position_.y < lb_edge_.y)
		position_.y = lb_edge_.y;
	if (position_.x > rt_edge_.x)
		position_.x = rt_edge_.x;
	if (position_.y > rt_edge_.y)
		position_.y = rt_edge_.y;
    return position_ == old_pos;
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


