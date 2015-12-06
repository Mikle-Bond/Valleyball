#ifndef EQUATION
#define EQUATION
#include <math.h>

#define WRONG -1


//just positive root
double PositiveRoot(double a, double b, double c)
{
    if (a == 0.)
    {
        if(b == 0.) return WRONG;
        if(b != 0. && c >= 0.) return WRONG;
        return -b/c;
    }
    else
    {
        if(b == 0.)
        {
            if (c == 0.) return 0.;
            if (a*c < 0.) return WRONG;
            else return sqrt(-a/c);
        }
        if(c == 0.)
        {
            if(a*b < 0.) return 0.;
            return -a/b;
        }
        double d = b*b - 4. * a * c;
        if(d > 0.)
        {
            return ( -b + sqrt(d) ) / (2. * a);
        }
    }
    return WRONG;
}

double NegativeRoot(double a, double b, double c)
{
    if (a == 0.)
    {
        if(b == 0. && c!= 0.) return -WRONG;
        if(b != 0. && c <= 0.) return -WRONG;
        return -b/c;
    }
    else
    {
        if(b == 0.)
        {
            if (c == 0.) return 0.;
            if (a*c > 0.) return -WRONG;
            else return sqrt(-a/c);
        }
        if(c == 0.)
        {
            if(a*b > 0.) return 0.;
            return -a/b;
        }
        double d = b*b - 4. * a * c;
        if(d > 0.)
        {
            return ( -b - sqrt(d) ) / (2. * a);
        }
    }
    return -WRONG;
}
#endif // EQUATION

