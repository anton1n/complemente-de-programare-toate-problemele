#include "Header.h"

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

struct Optiuni analiza(int argc, char**argv)
{
	struct Optiuni op;

	if(argc ==1 )
	{
		op.metoda = 1;
		op.n=100;
		op.li=0;
		op.ls=1;
		op.i=0;

		return op;
	}

	if(strcmp(argv[1],"-d")==0)
	{
		op.metoda  = 0;
	}
	else if(strcmp(argv[1], "-t")==0)
	{
		op.metoda = 1;
	}
	else if(strcmp(argv[1], "-s")==0)
	{
		op.metoda = 2;
	}

	op.n = atoi(argv[2]);

	op.li = atoi(argv[3]);

	op.ls = atoi(argv[4]);

	op.i = atoi(argv[5]) - 1;

	return op;
}

double calcul(struct Optiuni op, double (*integrale[5])(double))
{
	if(op.metoda == 0)
	{
		return integralaDreptunghi(op.li, op.ls, op.n, integrale[op.i]);
	}
	else if(op.metoda == 1)
	{
		return integralaTrapez(op.li, op.ls, op.n, integrale[op.i]);
	}
	else if(op.metoda == 2)
	{
		return integralaSimpson(op.li, op.ls, op.n, integrale[op.i]);
	}

	return 0;
}
