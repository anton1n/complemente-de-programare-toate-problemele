#include "Header.h"

union Rezultat functie(char * nume, int nr, ...)
{
	int min, max, i, val;
	double ma, mg;
	va_list ptr;

	va_start(ptr, nr);

	union Rezultat rezultat;

	if( strcmp(nume,"media aritmetica")==0 )
	{
		ma = 0;
		for(i=0;i<nr;++i)
		{
			ma += va_arg(ptr, int);
		}
		rezultat.d = ma/nr;
	}
	else if (strcmp(nume,"media geometrica")==0)
	{
		mg = 1;
		for(i=0;i<nr;++i)
		{
			mg *= va_arg(ptr, int);
		}
		rezultat.d = sqrt(mg);
	}
	else if (strcmp(nume,"minim")==0)
	{
		min = va_arg(ptr,int);
		for(i = 1;i<nr;++i)
		{
			val = va_arg(ptr,int);
			if (val < min)
			{
				min = val;
			}	
		}
		rezultat.i = min;
	}
	else if (strcmp(nume,"maxim")==0)
	{
		max = va_arg(ptr,int);
		for(i=1;i<nr;++i)
		{
			val = va_arg(ptr,int);
			if (val > max)
			{
				max = val;
			}
		}
		rezultat.i = max;
	}
	else{
		puts("Invalid!");
	}

	va_end(ptr);
	return rezultat;				
}
