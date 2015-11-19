#include "sam.h"
#include "manager.h"


SamThePlayer::SamThePlayer(const Vector2D &left, const Vector2D &right)
:
	Player(left, right, 0.2, 0.05, 0.5)
{

}

void SamThePlayer::idle(void)
{
	Manager& mgr = Manager::getManager();
	Ball& ball = mgr.getBall();	
}

Vector2D SamThePlayer::get_force(void)
{
	// Here:
	// bPos -- position vector
	// bSpd -- speed vector 
	// bAcc -- acceleration vector
	
}

