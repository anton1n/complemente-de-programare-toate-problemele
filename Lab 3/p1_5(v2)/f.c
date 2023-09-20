#include "Header.h"

char *conversieHexa(unsigned int nr)
{
	int rest, i=0;

	int digits = 0;
    int temp = nr;
    while (temp != 0) {
        digits++;
        temp /= 16;
	}
	char *c = malloc(digits+1);

	if(digits==0)
	{
		c[0]='0';
		return c;
	}
	//printf("%d", digits);
	i = digits -1;
	while(nr!=0)
	{
		//puts("ok ");
		rest = nr%16;
		if(rest<10)
		{
			//rest+=48;
			c[i] = rest+ '0';
		}
		else
		{
			//rest+=55;
			c[i] = rest - 10 + 'A';
		}
		//c=(char*)realloc(c,sizeof(char)*(i+1));
		//c[i] = rest;
		--i;
		nr/=16;
	}

	c[digits] = '\0';

	if(digits == 1)
	{
		c[1] = c[0];
		c[0] = '0';
		c[2] = '\0';
	}

	//puts(c);
	return c;
}
