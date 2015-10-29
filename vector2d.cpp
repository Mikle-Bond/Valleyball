#include "vector2d.h"
#include <cmath>

using std::sqrt;

Vector2D::Vector2D(double _x = 0.0, double _y = 0.0) :
    x(_x), y(_y)
{

}

Vector2D::~Vector2D()
{

}

Vector2D &Vector2D::operator +=(const Vector2D &rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2D &Vector2D::operator *=(double a)
{
    x *= a;
    y *= a;
    return *this;
}

Vector2D &Vector2D::normalize()
{
    double a = sqrt(x*x + y*y);
    double y = y / a;
    x = x / a;
    return *this;
}

Vector2D Vector2D::normal()
{
    return Vector2D(*this).normalize();
}

