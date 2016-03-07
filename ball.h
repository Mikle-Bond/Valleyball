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
/*
 *Ball is a class. Ball can move. Whatever you want you know
 *it's radius(get_radius()), accelaration(get_accel()), speed(get_cpeed),
 * mass(get_Mass()) and, as a Movable(get_pos()), position. You can push
 * Ball by force - Ball::push(Vector2D(-1, 0)).
 * function Ball::IsCrossing(Block) isn't good enough but now it shows
 * Vertical and Horizontal crossing
*/
class Ball : public Movable
{
    Vector2D acceleration;//by external force, if i need it here???
    double _mass;
    double radius_;

public:
//-------------------------------------------------------------------------------------------------
    Ball(const Vector2D &left = Vector2D(-1., 0.), const Vector2D &right = Vector2D(1.0, 1.0),
         const Vector2D &st_position = Vector2D(0.5, 0.5), const Vector2D &st_speed = Vector2D(),\
         Vector2D accel = Vector2D(0, -0.0981), double mass = 1, double radius = 0.005)\
        :Movable(left, right, st_position, st_speed), acceleration(accel)\
        ,_mass(mass),radius_(radius)
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
    inline double get_radius() const
    {
        return radius_;
    }
//-------------------------------------------------------------------------------------------------
    inline double get_Mass() const
    {
        return _mass;
    }
//-------------------------------------------------------------------------------------------------
    void push(Vector2D f);
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
    bool move() override;
//=================================================================================================
    int IsCrossing (const Block &block) const;//i hope that block is orientated
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

