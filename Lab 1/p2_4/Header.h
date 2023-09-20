#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <math.h>

double f0(double);
double f1(double);
double f2(double);
double f3(double);
double f4(double);
double integralaTrapez(double a, double b, unsigned int n, double (*f)(double));
double integralaDreptunghi(double a, double b, unsigned int n, double (*f)(double));
double integralaSimpson(double a, double b, unsigned int n, double (*f)(double));


#endif
