#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <math.h>

struct MENU_ITEM{
	char *nume;
	double (*f) ( double a, double b, unsigned int n, double (*) (double));
};
int menu(struct MENU_ITEM meniu[], unsigned int nf, char *msg);
double f(double);
double integralaTrapez(double a, double b, unsigned int n, double (*pf)(double));
double integralaDreptunghi(double a, double b, unsigned int n, double (*pf)(double));
double integralaSimpson(double a, double b, unsigned int n, double (*pf)(double));

#endif
