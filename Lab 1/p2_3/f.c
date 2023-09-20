#include "Header.h"

int menu(struct MENU_ITEM meniu[], unsigned int nf, char *msg)
{
	int optiune;
	register unsigned int i;
	puts(msg);
	for( i = 0 ; i < nf ; ++i )
	{
		printf("\t%d - %s\n", i + 1 , meniu[i].nume);
	}
	printf("\t0 - exit\n");
        printf("\t >> ");
	scanf("%d",  &optiune);
	return optiune;
}
double f(double x)
{
	double a;

	a = sin( exp(2 * x) + 3 );

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
