#include "sam.h"
#include "manager.h"
#include "equation.h"
#include <math.h>

// it is not very wrong, but don't complete
double SamThePlayer::were(Ball& ball)
{


        double t = 0;
        if(ball.get_speed().y > 0)
        {
            t = ball.get_speed().y / ball.get_accel().y;

            double ym = ball.get_pos().y + ball.get_speed().y * t - ball.get_accel().y * t*t / 2;

            t += PositiveRoot(1, 0, - 2 * ym / ball.get_accel().y);//????!!!!
        }
        else //vy <= 0
        {
            t = PositiveRoot(1, 2 * ball.get_speed().y / ball.get_accel().y, - 2 * ball.get_pos().y / ball.get_accel().y);
        }
        return ball.get_pos().x + ball.get_speed().x * t;

}



//return vector, which means angle, by which we need push the ball
//i suзpouse that x-position of net == 0
// i need have strong think about it
Vector2D SamThePlayer::How()
{
    double x1 = 0, ym = 0;
    double vy;
    double vx;

    for (int i = 0; i < 4 && x1 > -1 && ym < 2; ++i)
    {
        if(side)
        {
            x1 = (1 + x1) / 2;
            ym = Manager::getNet("twall").b.y - (i + 1) * Manager::getBall("ball").get_Radius();
        }
        else
        {
            x1 = (-1 + x1) / 2;
            ym = Manager::getNet("net").b.y + (i + 1) * Manager::getBall("ball").get_Radius();
        }
        vy = sqrt(Manager::getBall("ball").accel().y * 2 * ym);
        vx = x1 * sqrt(Manager::getBall("ball").accel().y / (ym * 2)) / 2;

        if((vx*vx + vy*vy) < get_max_force() * Manager::getStep() / Manager::getBall("ball").get_Mass())
            return Vector2D(vx, vy);
    }

    return Vector2D(0., 0.);
}

SamThePlayer::SamThePlayer(const Vector2D &left, const Vector2D &right, bool Side = false)
:
    Player(left, right, 0.2, 0.05, 0.5), side(Side)
{

}

bool SamThePlayer::move(double dt)
{

}

void SamThePlayer::idle()
{
    double x = were(Manager::getBall("ball"));
    double vx = x / Manager::getStep();
    if(vx < max_speed_)
        speed = Vector2D(x / Manager::getStep(), 0);
    else
        speed = Vector2D(max_speed_, 0);
}



Vector2D SamThePlayer::get_force(Manager &Mng)
{
    return How(Mng) / Mng.getStep();
	// Here:
	// bPos -- position vector
	// bSpd -- speed vector 
	// bAcc -- acceleration vector
	
}

