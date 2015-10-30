#ifndef VECTOR2D_H
#define VECTOR2D_H


struct Vector2D
{
    double x;
    double y;
    explicit Vector2D(double _x = 0.0, double _y = 0.0);
    ~Vector2D();

    Vector2D &operator +=(const Vector2D &rhs);
    Vector2D &operator *=(double a);

    // make this vector normal
    Vector2D &normalize(void);

    // build a normal copy of *this
    Vector2D normal(void);

//    static Vector2D unit(double phi); -- do we need it?
};

#endif // VECTOR2D_H
