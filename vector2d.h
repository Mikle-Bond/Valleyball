#ifndef VECTOR2D_H
#define VECTOR2D_H


struct Vector2D
{
    double x;
    double y;
    explicit Vector2D(double _x = 0.0, double _y = 0.0);
    ~Vector2D();
};

#endif // VECTOR2D_H
