#include "vector2d.h"
#include <cmath>

using std::sqrt;

Vector2D::Vector2D(double _x, double _y) 
:
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

Vector2D operator +(const Vector2D &lt, const Vector2D &rt)
{
    Vector2D temp(lt);
    temp += rt;
    return temp;
}

Vector2D &Vector2D::operator -=(const Vector2D &rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2D operator -(const Vector2D &lt, const Vector2D &rt)
{
    Vector2D temp(lt);
    temp -= rt;
    return temp;
}

Vector2D &Vector2D::operator *=(double a)
{
    x *= a;
    y *= a;
    return *this;
}

Vector2D &Vector2D::operator /=(double a)
{
	return this->operator*=(1.0 / a);
}

Vector2D operator *(const Vector2D &lt, double a)
{
    Vector2D temp(lt);
    temp *= a;
    return temp;
}

Vector2D operator *(double a, const Vector2D &rt)
{
    Vector2D temp(rt);
    temp *= a;
    return temp;
}

Vector2D operator /(const Vector2D &lt, double a)
{
	Vector2D temp = lt;
	temp /= a;
	return temp;
}

bool operator==(const Vector2D &lt, const Vector2D &rt)
{
	return (lt.x == rt.x) && (lt.x == rt.y);
}

bool operator!=(const Vector2D &lt, const Vector2D &rt)
{
	return !(lt == rt);
}

Vector2D &Vector2D::normalize()
{
    double a = sqrt(x*x + y*y);
    y = y / a;
    x = x / a;
    return *this;
}

Vector2D Vector2D::normal()
{
    return Vector2D(*this).normalize();
}

double Vector2D::operator()(const Vector2D & rhs)
{
	return x * rhs.x + y * rhs.y;
}

