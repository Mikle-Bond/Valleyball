#ifndef MOVABLE_H
#define MOVABLE_H

#include "vector2d.h"

// Movable is a point, that can be moved from lb_edge_ on the 
// bottom-left, to rt_edge_ on the top-right. Only in this rectangle.
// It has it's speed and position.

class Movable
{
public:
	Movable(const Vector2D &left, const Vector2D &right, 
		const Vector2D &st_position, const Vector2D &st_speed);
	virtual ~Movable() = 0;
	Vector2D get_pos(void);

	// Moving block on speed*dt
	virtual void move(double dt); 	

	// Can be canged outside. In geberal.
	Vector2D speed;
private:
	Vector2D position_;
	Vector2D lb_edge_;
	Vector2D rt_edge_;
};

#endif // MOVABLE_H

