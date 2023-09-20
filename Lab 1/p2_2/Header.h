#ifndef HEADER_H_
#define HEADER_H_

#include <math.h>
//double (*pf)(double);
double f(double);
double integralaTrapez(double a, double b, unsigned int n, double (*pf)(double));

#endif
