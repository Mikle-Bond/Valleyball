#ifndef OBJECTS
#define OBJECTS
#include "vector2D.h"


struct Force
{
    vector2D F;

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

class Ball
{
    double _x;
    double _y;
    double _vx;
    double _vy;
    Force _force;//external force, if i need it here???
    double _mass;
    double _Radius;

public:
    Ball(double x = 0, double y = 0, double vx = 0, double vy = 0,\
         double force, double mass = 1, double radius = 0.1)//list of initialization?
    {
        _x = x;
        _y = y;
        _vx = vx;
        _vy = vy;
        _force.Fx = force.Fx;
        _force.Fy = force.Fy;
        _mass = mass;
        _Radius = radius;
    }
//-------------------------------------------------------------------------------------------------
    double get_x() const
    {
        return _x;
    }

    double get_y() const
    {
        return _y;
    }

    double get_Vx() const
    {
        return _vx;
    }

    double get_Vy() const
    {
        return _vy;
    }
//--------------------------------------------------------------------------------------------------
    void push(Force f, double dt)
    {
        vx += (f.Fx * dt) / mass;
        vy += (f.Fy * dt) / mass;
    }
    void next_step(double dt)
    {
        _x += vx * dt;
        _y += vy * dt;
        vx += (force.Fx + this->_force) * dt / mass;
        vy += (force.Fy + this->_force) * dt / mass;
    }
};
//===================================================================================================

#endif // OBJECTS

