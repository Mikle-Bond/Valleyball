#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "block.h"

class Player
{
public:
	class position : public Block
	{
	public:
		position(Vector2D &left, Vector2D &right, 
			double height, double position);
		Vector2D get_pos(void);
		Vector2D get_head(void);
		// here we understend position as
		// lt_edge + (rt_edge - lt_edge) * pos_mul;
	private:
		Vector2D lt_edge_;
		Vector2D rt_edge_;
		double height_;
		double pos_mul_;
	};

	Player(Vector2D &left, Vector2D &right, double height,
		double max_speed, double max_force, double curr = 0.5);
	~Player();

	virtual void idle(void);
	virtual Vector2D get_force(void);

	position pos;
private:
	double max_force_;
	double max_speed_;
};

#endif // PLAYER_H
