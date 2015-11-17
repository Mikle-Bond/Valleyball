#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "block.h"
#include "movable.h"

class Player : public Movable
{
public:
	Player(const Vector2D &left, const Vector2D &right, double height,
		double max_speed, double max_force, double curr = 0.5);
	virtual ~Player();

	virtual void idle(void);
	virtual Vector2D get_force(void);

private:
	double height_; // maybe we don't need it.
	double max_force_;
	double max_speed_;
	Vector2D honey_point;
};

#endif // PLAYER_H


