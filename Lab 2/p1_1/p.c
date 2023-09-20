#include "Header.h"

int main(void)
{
	union Calendar cal;
	cal.x = 0;
	afisareBinara(cal.x);
	
	citire(&cal);
	
	//printf("%u %u %u", cal.Data.zi, cal.Data.luna, cal.Data.an);
	afisareBinara(cal.x);
	return 0;
}
