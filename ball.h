#ifndef BALL
#define BALL
#include "vector2d.h"
#include "block.h"
#include "movable.h"

#define NONE_CROSS       0
#define VERTICAL_CROSS   1
#define HORIZONTAL_CROSS 2
#define SLOPPING_CROSS   3

class Ball : public Movable
{
    Vector2D acceleration;//by external force, if i need it here???
    double _mass;
    double _Radius;

public:
    Vector2D X0Y0;
//-------------------------------------------------------------------------------------------------
    Ball(const Vector2D &left, const Vector2D &right,
         const Vector2D &st_position, const Vector2D &st_speed,\
         Vector2D accel = Vector2D(0, 0.0981), double mass = 1, double radius = 0.01)\
        :Movable(left, right, st_position, st_speed), X0Y0(st_position),acceleration(accel)\
        ,_mass(mass),_Radius(radius)
    {
    }
    ~Ball(){}
//-------------------------------------------------------------------------------------------------
    inline Vector2D get_speed() const
    {
        return speed;
    }
    inline Vector2D get_accel()
    {
        return acceleration;
    }
//-------------------------------------------------------------------------------------------------
    inline double get_Radius() const
    {
        return _Radius;
    }
//-------------------------------------------------------------------------------------------------
    inline double get_Mass()
    {
        return _mass;
    }
//-------------------------------------------------------------------------------------------------
    void push(Vector2D f, double dt)
    {
        speed.x += (f.x / _mass + acceleration.x) * dt;
        speed.y += (f.y / _mass + acceleration.y) * dt;
    }
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
    bool move(double dt) override
    {
        speed.x += (acceleration.x) * dt;
        speed.y += (acceleration.y) * dt;

        return Movable::move(dt);// may be it isn't need becose of we haven't crossing with walls
    }
/*
 * now only vertical and horizontal blocks, may be sloping in the future
 * i need to think about it
*/
    int IsCrossing (const Block &block)//i hope that block is orientated
    {
        if (block.a.x == block.b.x)
            if(((speed.x > 0) &&  (get_pos().x >= block.a.x))
            || ((speed.x < 0) &&  (get_pos().x <= block.a.x))) return VERTICAL_CROSS;

        if (block.a.y == block.b.y)
            if(((speed.y > 0) &&  (get_pos().y >= block.a.y))
            || ((speed.y < 0) &&  (get_pos().y <= block.a.y))) return HORIZONTAL_CROSS;
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

