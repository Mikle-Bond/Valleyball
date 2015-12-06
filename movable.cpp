#include "movable.h"

Movable::Movable(const Vector2D &left, const Vector2D &right, 
	const Vector2D &st_position, const Vector2D &st_speed)
:
    lWall_(left),
    rWall_(right),
    Pos_(st_position),
	speed(st_speed)
{

}

Vector2D Movable::get_pos(void)
{
    return Pos_;
}
void Movable::changeXdir()
{
    speed.x = -speed.x;
}
void Movable::changeYdir()
{
    speed.y = -speed.y;
}

bool Movable::move(double dt)
{
    if(GameWorld.InBox(Pos))
    {
        Vector2D offset = speed * dt;
        Pos += offset;
        return true;
    }

    if (Pos_.x < GamesWorld.lWall.x)
        Pos_.x = GamesWorld.lWall.x;
    if (Pos_.y < GamesWorld.lWall.y)
        Pos_.y = GamesWorld.lWall.y;
    if (Pos_.x > GamesWorld.rWall.x)
        Pos_.x = GamesWorld.rWall.x;
    if (Pos_.y > GamesWorld.rWall.y)
        Pos_.y = GamesWorld.rWall.y;
    return false;
}

Movable::~Movable() {}


