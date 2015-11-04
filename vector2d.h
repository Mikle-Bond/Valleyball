#ifndef VECTOR2D_H
#define VECTOR2D_H


struct Vector2D
{
    explicit Vector2D(double _x = 0.0, double _y = 0.0);
    ~Vector2D();

    Vector2D &operator +=(const Vector2D &rhs);
    Vector2D &operator -=(const Vector2D &rhs);
    Vector2D &operator *=(double a);

    // make this vector normal
    Vector2D &normalize(void);

    // build a normal copy of *this
    Vector2D normal(void);

    double x;
    double y;
//    static Vector2D unit(double phi); -- do we need it?
};

Vector2D operator +(const Vector2D &lt, const Vector2D &rt);
Vector2D operator -(const Vector2D &lt, const Vector2D &rt);
Vector2D operator *(const Vector2D &lt, double a);
Vector2D operator *(double a, const Vector2D &rt);

#endif // VECTOR2D_H
