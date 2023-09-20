#include "Header.h"

double f(double x)
{
	return sin( exp(2 * x) + 3 );
}
double integralaTrapez(double a, double b, unsigned int n, double (*pf)(double))
{
	double sum;
	double x;
	double dx;
	double eps = 1e-4;

	dx = (b - a) / n;
	sum = ((*pf)(a) + (*pf)(b)) / 2;

	for( x = a + dx ; fabs( x + dx - b ) > eps ; x = x + dx)
	{
		sum = sum + ((*pf)(x));
	}

	sum = sum * dx;

	return sum;
}
