#ifndef BALL
#define BALL
#include "vector2d.h"
#include "block.h"

#define NONE_CROSS       0
#define VERTICAL_CROSS   1
#define HORIZONTAL_CRASS 2
#define SLOPPING_CROSS   3

#if 0
struct Force        //is it usefull????
{
    Vector2D F;

    Force(double fx = 0, double fy = 0):F(fx, fy)
    {
    }
#if 0
    double value;
    double angle;//from horisont
    Force(double val = 0, double ang = 0)
    {
        value = val;
        angle = ang;
    }
    //may be (double *F) and create array of 2 elements: Fx and Fy - can be changig for 3D easier
#endif
};
#endif
class Ball
{
    Vector2D coordinates;
    Vector2D velocity;
    Force force;//external force, if i need it here???
    double _mass;
    double _Radius;

public:
    Ball(double x = 0, double y = 0, double vx = 0, double vy = 0,\
         double xforce = 0,double yforce = 9.81, double mass = 1, double radius = 0.1)\
        :coordinates(x, y),velocity(vx, vy),force(xforce, yforce),_mass(mass),_Radius(radius)
    {
    }
//-------------------------------------------------------------------------------------------------
    double get_x() const
    {
        return coordinates.x;
    }

    double get_y() const
    {
        return coordinates.y;
    }

    double get_Vx() const
    {
        return velocity.x;
    }

    double get_Vy() const
    {
        return velocity.y;
    }
//-------------------------------------------------------------------------------------------------
    void push(Force f, double dt)
    {
        f.F+=this->force.F;
        velocity.x += (f.F.x * dt) / mass;
        velocity.y += (f.F.y * dt) / mass;
    }
//-------------------------------------------------------------------------------------------------
    void next_step(double dt)
    {
        coordinates.x += vx * dt;
        coordinates.y += vy * dt;

        velocity.x += (this->force.F.x) * dt / mass;
        velocity.y += (this->force.F.y) * dt / mass;
    }
/*
 * now only vertical and horizontal blocks, may be sloping in the future
 * i need to think about it
*/
    int IsCrossing (const Block &block)//i hope that block is orientated
    {
        if (block.a.x == block.b.x)
            if(((velocity.x > 0) &&  (coordinates.x >= block.a.x))
            || ((velocity.x < 0) &&  (coordinates.x <= block.a.x))) return VERTICAL_CROSS;

        if (block.a.y == block.b.y)
            if(((velocity.y > 0) &&  (coordinates.y >= block.a.y))
            || ((velocity.y < 0) &&  (coordinates.y <= block.a.y))) return VERTICAL_CROSS;
    }

};
//===================================================================================================
/*
 *   \(x2,y2)           if(x1 != x2)
 *    \                     if(x > x2 && x < x1)
 *  O->\o->                         x >= y * (x2-x1)/(y2-y1)
 *     o\
 *     | \(x1,y1)
 *     V
 *
*/
#endif // BALL

