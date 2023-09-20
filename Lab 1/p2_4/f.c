#include "Header.h"

double f0(double x)
{
	double a;

	a = exp( -x * x );
	return a;
}
double f1(double x)
{
	double a;

	a = x;

	return a;
}
double f2(double x)
{
	double a;

	a = x * x;

	return a;
}
double f3(double x)
{
	double a;

	a = sqrt(1 + 1 / x);

	return a;
}
double f4(double x)
{
	double a;

	a = x / ( 1 + x ) ;

	return a;
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
double integralaDreptunghi(double a, double b, unsigned int n, double (*pf)(double))
{
	double sum;
	double x;
	double dx;
	double eps = 1e-4;

	dx = ( b - a ) / n;
	sum = ((*pf)(a) * (*pf)(b));

	for( x = a + dx ; fabs( x + dx - b ) > eps ; x = x + dx)
	{
		sum = sum + ((*pf)(x));
	}

	sum = sum * dx;

	return sum;
}
double integralaSimpson(double a, double b, unsigned int n, double (*pf)(double))
{
	double sum;
	double x;
	double dx;
	double eps = 1e-4;

	dx = (b - a) / n;
	sum = ( b - a ) / 6 * ((*pf)(a) + 4 * (*pf)(( a + b ) / 2 ) +(*pf)(b));

	for( x = a + dx ; fabs( x + dx - b ) > eps ; x = x + dx)
	{
		sum = sum + ((*pf)(x));
	}

	sum = sum * dx;

	return sum;
}
