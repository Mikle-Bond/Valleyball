#include "movable.h"
#if 0
Movable::Movable(const Vector2D &left, const Vector2D &right, 
	const Vector2D &st_position, const Vector2D &st_speed)
:
	lb_edge_(left),
	rt_edge_(right),
	position_(st_position),
	speed(st_speed)
{

}
#endif
Vector2D Movable::get_pos(void)
{
    return Pos;
}

bool Movable::move(double dt)
{
    if(GameWorld.InBox(Pos))
    {
        Vector2D offset = speed * dt;
        Pos += offset;
        return true;
    }

    if (Pos.x < GamesWorld.lWall.a.x)
        Pos.x = GamesWorld.lWall.a.x;
    if (Pos.y < GamesWorld.lWall.a.y)
        Pos.y = GamesWorld.lWall.a.y;
    if (Pos.x > GamesWorld.rWall.b.x)
        Pos.x = GamesWorld.rWall.b.x;
    if (Pos.y > GamesWorld.rWall.b.y)
        Pos.y = GamesWorld.rWall.b.y;
    return false;
}

Movable::~Movable() {}


