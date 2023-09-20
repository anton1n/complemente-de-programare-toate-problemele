#include "Header.h"
void afisareBinara(unsigned int data)
{
	unsigned int nr=sizeof(unsigned int)<<3;
	unsigned int MASK=(~0u)>>1;
	MASK =~MASK;
	unsigned int c;
	while(nr--)
	{
		c=(data & MASK)>>nr;
		putchar(c+'0');
		if(!(nr&07))
			{
				putchar(' ');
			}
			MASK>>=(unsigned int) 1u;
	}
	putchar('\n');
}

void citire(union Calendar *cal)
{
	unsigned int n,i, n2;
	char luna[10];

	puts("Inreoduceti ziua, luna si anul: ");
	scanf("%u",&n);
	cal->Data.zi = n;
	
	scanf("%s",luna);
	for(i=0;i<strlen(luna);++i)
	{
		luna[i] = tolower(luna[i]);
	}
	if(strcmp(luna, "ianuarie")==0)
	{
		cal->Data.luna = 1;		
	}
	else if(strcmp(luna, "februarie")==0)
	{
		cal->Data.luna = 2;		
	}
	else if(strcmp(luna, "martie")==0)
	{
		cal->Data.luna = 3;		
	}
	else if(strcmp(luna, "aprilie")==0)
	{
		cal->Data.luna = 4;		
	}
	else if(strcmp(luna, "mai")==0)
	{
		cal->Data.luna = 5;		
	}
	else if(strcmp(luna, "iunie")==0)
	{
		cal->Data.luna = 6;		
	}
	else if(strcmp(luna, "iulie")==0)
	{
		cal->Data.luna = 7;		
	}
	else if(strcmp(luna, "august")==0)
	{
		cal->Data.luna = 8;		
	}
	else if(strcmp(luna, "septembrie")==0)
	{
		cal->Data.luna = 9;		
	}
	else if(strcmp(luna, "octombrie")==0)
	{
		cal->Data.luna = 10;		
	}
	else if(strcmp(luna, "noiembrie")==0)
	{
		cal->Data.luna = 11;		
	}
	else if(strcmp(luna, "decembrie")==0)
	{
		cal->Data.luna = 12;		
	}

	scanf("%u",&n2);

	cal->Data.an = n2;


}
