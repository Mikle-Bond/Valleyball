#ifndef BALL
#define BALL
#include "vector2d.h"
#include "block.h"
#include "movable.h"
#include "equation.h"
#include "manager.h"

#define NONE_CROSS       0
#define CROSS           -1
#define VERTICAL_CROSS   1
#define HORIZONTAL_CROSS 2
#define SLOPPING_CROSS   3

class Ball : public Movable
{
    Vector2D acceleration;//by external force, if i need it here???
    double _mass;
    double _Radius;

public:
//-------------------------------------------------------------------------------------------------
    Ball(const Vector2D &left = Vector2D(-1., 0.), const Vector2D &right = Vector2D(1.0, 1.0),
         const Vector2D &st_position = Vector2D(0.5, 0.5), const Vector2D &st_speed = Vector2D(),\
         Vector2D accel = Vector2D(0, -0.0981), double mass = 1, double radius = 0.005)\
        :Movable(left, right, st_position, st_speed), acceleration(accel)\
        ,_mass(mass),_Radius(radius)
    {
    }
    ~Ball(){}
//-------------------------------------------------------------------------------------------------
    inline Vector2D get_speed() const
    {
        return speed;
    }
    inline Vector2D get_accel() const
    {
        return acceleration;
    }
//-------------------------------------------------------------------------------------------------
    inline double get_Radius() const
    {
        return _Radius;
    }
//-------------------------------------------------------------------------------------------------
    inline double get_Mass() const
    {
        return _mass;
    }
//-------------------------------------------------------------------------------------------------
    void push(Vector2D f)
    {
        speed.x += (f.x + acceleration.x) * Manager::getSingleton().getStep();
        speed.y += (f.y + acceleration.y) * Manager::getSingleton().getStep();
    }
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
    bool move() override
    {
        speed.x += (acceleration.x) * Manager::getSingleton().getStep();
        speed.y += (acceleration.y) * Manager::getSingleton().getStep();

        return Movable::move(dt);// may be it isn't need becose of we haven't crossing with walls
    }
//=================================================================================================
    int IsCrossing (const Block &block) const //i hope that block is orientated
    {
        double x0 = get_pos().x;
        double y0 = get_pos().y;

        if (block.b.x - block.a.x == 0)
        {
            double b = -block.a.x;
            if(((block.a.y - block.b.y > 0) && (y0 > block.b.y && y0 < block.a.y))\
                || ((block.a.y - block.b.y < 0) && (y0 < block.b.y && y0 > block.a.y)))
                    if(MyUseful::IsRoots(1, -2 * y0, -_Radius*_Radius + (b - x0)*(b - x0)))
                        return CROSS;
        }
        else
        {
           double k = (block.b.y - block.a.y) / (block.b.x - block.a.x);
           double b = block.b.y - k * block.b.x;

           if(((block.a.x - block.b.x > 0) && (x0 > block.b.x && x0 < block.a.x))\
               || ((block.a.x - block.b.x < 0) && (x0 < block.b.x && x0 > block.a.x)))
                if (MyUseful::IsRoots(k*k + 1, -2 * (x0 - y0 * k), - _Radius*_Radius - 2 * y0 * b + x0*x0))
                   return CROSS;
        }
        return NONE_CROSS;

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

