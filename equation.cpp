#include "equation.h"
#include <math.h>


double MyUseful::absd(double x)
{
    if (x < 0) return -x;
    return x;
}
int MyUseful::sign(double x)
{
    if (x > 0)  return 1;
    if (x < 0)  return -1;
    return 0;
}

//just positive root
double MyUseful::PositiveRoot(double a, double b, double c)
{
    if (a == 0.)
    {
        if(b == 0.) return POSITIVE_WRONG_ROOT;
        if(b != 0. && c >= 0.) return POSITIVE_WRONG_ROOT;
        return -b/c;
    }
    else
    {
        if(b == 0.)
        {
            if (c == 0.) return 0.;
            if (a*c < 0.) return POSITIVE_WRONG_ROOT;
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
    return POSITIVE_WRONG_ROOT;
}

double MyUseful::NegativeRoot(double a, double b, double c)
{
    if (a == 0.)
    {
        if(b == 0. && c!= 0.) return NEGATIVE_WRONG_ROOT;
        if(b != 0. && c <= 0.) return NEGATIVE_WRONG_ROOT;
        return -b/c;
    }
    else
    {
        if(b == 0.)
        {
            if (c == 0.) return 0.;
            if (a*c > 0.) return NEGATIVE_WRONG_ROOT;
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
    return NEGATIVE_WRONG_ROOT;
}

bool MyUseful::IsRoots(double a, double b, double c)
{
    if (a == 0.)
    {
        if(b == 0. && c!= 0.) return false;
        return true;
    }
    else
    {
        if(b == 0.)
        {
            if (a*c < 0.) return false;
            else return true;
        }
        if(c == 0.)
        {
            return true;
        }
        double d = b*b - 4. * a * c;
        if(d > 0.)
        {
            return true;
        }
    }
    return false;
}

