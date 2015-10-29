#include "block.h"

Block::Block(double ax, double ay, double bx, double by) :
    a(ax, ay), b(bx, by)
{

}

Block::Block(const Vector2D &_a, const Vector2D &_b) :
    a(_a), b(_b)
{

}

Block::~Block()
{

}
