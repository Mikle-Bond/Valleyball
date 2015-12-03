#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "block.h"
#include "movable.h"
#include "factory.h"

// Here we mean position of the Movable as a Block.a
class Player : public Movable, public Block
{
public:
	Player();
	Player(const Vector2D &left, const Vector2D &right, double height,
		double max_speed, double max_force, double curr = 0.5);
	virtual ~Player() = 0;

	virtual void init(const Vector2D &left, const Vector2D &right, 
		double height, double max_speed, double max_force, 
		double curr) = 0;
	virtual void move(double dt) override;
	virtual void idle(void);
	virtual Vector2D get_force(void);

private:
	void set_block(void);
	double height_; // maybe we don't need it.
	double max_force_;
	double max_speed_;
};

#endif // PLAYER_H


