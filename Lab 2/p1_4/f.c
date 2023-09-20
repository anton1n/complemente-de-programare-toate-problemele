#include "Header.h"

union Rezultat functie(char * nume, int first, ...)
{
	int min, max, i, val;
	double ma, mg;
	va_list ptr;

	va_start(ptr, first);
	union Rezultat rezultat;

	if( strcmp(nume,"media aritmetica")==0 )
	{

		i=0;
		ma = first;
		for(i=0;;++i)
		{
			val = va_arg(ptr,int);
			if(val == 0)
				break;
			ma += val;
		}
		++i;
		rezultat.d = ma/i;
	}
	else if (strcmp(nume,"media geometrica")==0)
	{
		mg = first;
		while(1)
		{
			val = va_arg(ptr,int);
			if(val == 0)
				break;
			mg *= val;
		}
		rezultat.d = sqrt(mg);
	}
	else if (strcmp(nume,"minim")==0)
	{
		min = first;
		while(1)
		{
			val = va_arg(ptr,int);
			if(val == 0)
				break;
			if (val < min)
			{
				min = val;
			}	
		}
		rezultat.i = min;
	}
	else if (strcmp(nume,"maxim")==0)
	{
		max = first;
		while(1)
		{
			val = va_arg(ptr,int);
			if(val == 0)
				break;
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
