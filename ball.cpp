#include "ball.h"
//-------------------------------------------------------------------------------------------------
    void Ball::push(Vector2D f)
    {
        speed.x += (f.x + acceleration.x) * Manager::getSingleton().getStep();
        speed.y += (f.y + acceleration.y) * Manager::getSingleton().getStep();
    }
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
    bool Ball::move()
    {
        speed.x += (acceleration.x) * Manager::getSingleton().getStep();
        speed.y += (acceleration.y) * Manager::getSingleton().getStep();

        return Movable::move();// may be it isn't need becose of we haven't crossing with walls
    }
//=================================================================================================
    int Ball::IsCrossing (const Block &block) const
    {
        double x0 = get_pos().x;
        double y0 = get_pos().y;

        if (block.b.x - block.a.x == 0)
        {
            double b = -block.a.x;
            if(((block.a.y - block.b.y > 0) && (y0 > block.b.y && y0 < block.a.y))\
                || ((block.a.y - block.b.y < 0) && (y0 < block.b.y && y0 > block.a.y)))
                    if(MyUseful::IsRoots(1, -2 * y0, -radius_*radius_ + (b - x0)*(b - x0)))
                        return CROSS;
        }
        else
        {
           double k = (block.b.y - block.a.y) / (block.b.x - block.a.x);
           double b = block.b.y - k * block.b.x;

           if(((block.a.x - block.b.x > 0) && (x0 > block.b.x && x0 < block.a.x))\
               || ((block.a.x - block.b.x < 0) && (x0 < block.b.x && x0 > block.a.x)))
                if (MyUseful::IsRoots(k*k + 1, -2 * (x0 - y0 * k), - radius_*radius_ - 2 * y0 * b + x0*x0))
                   return CROSS;
        }
        return NONE_CROSS;

    }

