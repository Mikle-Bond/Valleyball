#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "block.h"

// Block that can be moved along line
class Movable : private Block
{
public:
	Movable(const Vector2D &left, const Vector2D &right, 
		double height, double position);
	Vector2D get_pos(void);
	Vector2D get_head(void);

	// Allovs move bolck along the vector from left side to right 
	// (can be negative)
	void move_by(double meters); 	
	
	// I don't shure it sould exist. But if it so...
	// Moves the block as close as possible to the point
	// void move_to(Vector2D point);

private:
	// here we understend position as
	// lt_edge + (rt_edge - lt_edge) * direction;
	Vector2D lt_edge_;
	Vector2D rt_edge_;
	double pos_mul_;
	Vector2D direction_;
};

class Player : public Movable
{
public:
	Player(const Vector2D &left, const Vector2D &right, double height,
		double max_speed, double max_force, double curr = 0.5);
	~Player();

	virtual void idle(void);
	virtual Vector2D get_force(void);

private:
	double height_; // maybe we don't need it.
	double max_force_;
	double max_speed_;
	Vector2D honey_point;
};

#endif // PLAYER_H
