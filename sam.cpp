﻿#include "sam.h"
#include "manager.h"
#include "equation.h"
#include <math.h>

PEGISTRATE_PLAYER(SamThePlayer);


// it is not very wrong, but don't complete

double SamThePlayer::were()
{
        const Ball &ball = Manager::getSingleton().getBall("ball");

        double t = 0;
        if(ball.get_speed().y > 0)
        {
            t = ball.get_speed().y / ball.get_accel().y;

            double ym = ball.get_pos().y + ball.get_speed().y * t - ball.get_accel().y * t*t / 2;

            t += MyUseful::PositiveRoot(1, 0, - 2 * ym / ball.get_accel().y);//????!!!!
        }
        else //vy <= 0
        {
            t = MyUseful::PositiveRoot(1, 2 * ball.get_speed().y / ball.get_accel().y, - 2 * ball.get_pos().y / ball.get_accel().y);
        }
        return ball.get_pos().x + ball.get_speed().x * t;

}



//return vector, which means angle, by which we need push the ball
//i suзpouse that x-position of net == 0
// i need have strong think about it
Vector2D SamThePlayer::How()
{

    Manager &mng = Manager::getSingleton();

    double x1 = 0, ym = 0;
    double vy;
    double vx;

    for (int i = 0; i < 4 && x1 > -1 && ym < 2; ++i)
    {
        if(side)
        {
            x1 = (1 + x1) / 2;
            ym = mng.getNet("twall").b.y - (i + 1) * mng.getBall("ball").get_radius();
        }
        else
        {
            x1 = (-1 + x1) / 2;
            ym = mng.getNet("net").b.y + (i + 1) * mng.getBall("ball").get_radius();
        }
        vy = sqrt(mng.getBall("ball").get_accel().y * 2 * ym);
        vx = x1 * sqrt(mng.getBall("ball").get_accel().y / (ym * 2)) / 2;

        if((vx*vx + vy*vy) < getMaxForce() * mng.getStep() / mng.getBall("ball").get_Mass())
            return Vector2D(vx, vy);
    }

    return Vector2D(0., 0.);
}


SamThePlayer::SamThePlayer(const Vector2D &left, const Vector2D &right, bool Side = false)
:
    Player(left, right, 0.2, 0.05, 0.5), side(Side)
{

}

SamThePlayer::SamThePlayer()
:
    SamThePlayer(Vector2D(), Vector2D(1., 1.), false)
{

}

void SamThePlayer::init(const Vector2D &left, const Vector2D &right,
            double height, double max_speed, double max_force,
            double curr)
{
    initDefault(left, right, height, max_speed, max_force, curr);
}

bool SamThePlayer::move()
{
    return Player::move();
}

void SamThePlayer::idle()
{
    double x = were() - get_pos().x;
    double vx = x / Manager::getSingleton().getStep();
    if(MyUseful::absd(vx) < getMaxSpeed())
        speed = Vector2D(vx, 0);
    else
        speed = Vector2D(getMaxSpeed(), 0);
}



Vector2D SamThePlayer::get_force()
{
    return How() * (1.0 / Manager::getSingleton().getStep());
    // Here:
	// bPos -- position vector
	// bSpd -- speed vector 
	// bAcc -- acceleration vector	
}

SamThePlayer::~SamThePlayer()
{

}
