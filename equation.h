#ifndef EQUATION
#define EQUATION

#define POSITIVE_WRONG_ROOT -1
#define NEGATIVE_WRONG_ROOT  1

namespace MyUseful
{

double absd(double x);
int sign(double x);

double PositiveRoot(double a, double b, double c);
double NegativeRoot(double a, double b, double c);
bool IsRoots(double a, double b, double c);

}//namespace MyUseful

#endif // EQUATION

