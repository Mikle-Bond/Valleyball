#include "player.h"

void Player::set_block(void)
{
	a = this->get_pos();
	b = a + Vector2D(0.0, height_);
}

double Player::getMaxForce() const
{
    return max_force_;
}
double Player::getMaxSpeed()
{
    return max_speed_;
}

Player::Player()
:
	Player(Vector2D(), Vector2D(), 0.0, 0.0, 0.0)
{

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

void Player::initDefault(const Vector2D &left, const Vector2D &right, 
	double height, double max_speed, double max_force, 
	double curr)
{
	height_ = height;
	max_speed_ = max_speed;
	max_force_ = max_force;
	Movable::initMovable(left, right, (right - left) * curr + left, Vector2D());
	set_block();
}

bool Player::move(double dt)
{
    bool isOk = Movable::move(dt);
	set_block();
    return isOk;
}

