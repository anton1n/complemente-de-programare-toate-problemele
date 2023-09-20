#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

union Rezultat{
	int i;
	double d;
};

union Rezultat functie(char * nume, int first, ...);

#endif
