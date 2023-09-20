#include "Header.h"

struct Rez identificare(int nr, ...)
{
	struct Rez rezultat = {0};
	int i, val, aux, p1=0, p2=0, p3=0;
	va_list ptr;

	_Bool niciuna = 0;
	
	va_start(ptr, nr);

	aux = 0;
	aux = va_arg(ptr,int);
	for(i = 1; i<nr;++i)
	{
		val = va_arg(ptr, int);
		if(aux>val)
		{
			p1++;
			//rezultat.nmare++;
		}
		else if (aux<val)
		{
			p2++;
			//rezultat.nmic++;
		}
		else if (aux == val)
		{
			p3++;
			
		}
		
		if(p1 !=0 && p2!=0)
		{
			niciuna = 1;
		}

		if (val ==0)
		{
			rezultat.err=0;
			va_end(ptr);
			return rezultat;
		}

		aux = val;

	}

	if(niciuna)
	{
		rezultat.nmic=p2;
		rezultat.nmare=p1;
	}
	else if(p3!=0 &&p1==0 && p2==0)
	{
		rezultat.constant = 1;
	}
	else{
		if(p1!=0 && p3==0)
		{
			rezultat.sdesc = 1;
		}
		else if (p1!=0 && p3!=0)
		{
			rezultat.desc = 1;
		}

		if (p2!=0 && p3==0)
		{
			rezultat.scresc=1;
		}
		else if (p2!=0 && p3!=0)
		{
			rezultat.cresc=1;
		}
	}
	va_end(ptr);

	puts("\n");

	return rezultat;

}
