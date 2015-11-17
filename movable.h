#ifndef MOVABLE_H
#define MOVABLE_H

#include "vector2d.h"

// Movable is a poin, that can be moved from lt_edge_ on the left,
// to rt_edge_ on the right. It has it's speed and position.

class Movable
{
public:
	Movable(const Vector2D &left, const Vector2D &right, 
		const Vector2D &st_position, const Vector2D &st_speed);
	virtual ~Movable() = 0;
	Vector2D get_pos(void);

	// Moving block on speed*dt
	void move(double dt); 	

	// Can be canged outside. In geberal.
	Vector2D speed;
private:
	Vector2D position_;
	Vector2D lt_edge_;
	Vector2D rt_edge_;
};

#endif // MOVABLE_H

