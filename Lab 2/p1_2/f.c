#include "Header.h"

double suma(int nr, ...)
{
	unsigned int i;
	double s = 0;

	va_list ptr;
	va_start(ptr, nr);
	
	for(i=0;i<nr;++i)
	{
		s+=va_arg(ptr,double);
	}

	va_end(ptr);

	return s;
}
