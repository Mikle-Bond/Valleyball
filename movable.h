#ifndef MOVABLE_H
#define MOVABLE_H

#include "vector2d.h"
#include "block.h"
#if 0   //Mikle's class
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
#endif

class Movable
{
private:
    struct Box
    {
        //here must be vector2d!!!
        Block lWall;
        Block rWall;

        explicit Box(double rxd = 1., double ryd = 0., double rxu = 1., double ryu = 2.,\
                     double lxd = -1., double lyd = 0., double lxu = -1., double lyu = 2.):\
            rWall(rxd,ryd,rxu,ryu), lWall(lxd,lyd,lxu,lyu){}

        bool InBox(Vector2D pos)
        {
           return (pos.x < lWall.a.x) && (pos.y > lWall.a.y) &\
                   & (pos.x > rWall.b.x) && (pos.y < rWall.b.y);
        }

    }GamesWorld;
    Vector2D Pos;
public:
    Vector2D speed;

    explicit Movable(double startXpos = 0., double startYpos =  0.)\
            :GamesWorld(), Pos(startXpos, startYpos), speed(){}
    virtual ~Movable() = 0;

    //move object on speed*dt, if it possible
    virtual bool move(double dt);
    //return Pos
    Vector2D get_pos(void);
};

#endif // MOVABLE_H

