#ifndef MOVABLE_H
#define MOVABLE_H

#include "vector2d.h"
#include "block.h"
   //Mikle's class
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

    void changeXdir();
    void changeYdir();

	// Moving block on speed*dt
    virtual bool move(double dt);

	// Can be canged outside. In geberal.
	Vector2D speed;


private:
    Vector2D Pos_;
    Vector2D lWall_;
    Vector2D rWall_;
};


#endif // MOVABLE_H

