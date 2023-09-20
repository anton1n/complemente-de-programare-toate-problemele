#include <stdio.h>
#include <math.h>
#include "operatii.h"

void help(void)
{
	puts("");
	puts("-------------------------------------------");
	puts(" Program care calculează media aritmetica  ");
	puts(" si media geometrica a doua numere intregi ");
	puts(" citite de la tastatura                    ");
	puts("-------------------------------------------");
	puts("");
}

double mediaAritmetica(int x, int y)
{
	double mA;

	mA = (x + y)/(double)2;

	return mA;
}


double mediaGeometrica(int x, int y)
{
	double mG;

	mG = sqrt(x * y);

	return mG;
}

