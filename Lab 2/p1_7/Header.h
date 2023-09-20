#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct Optiuni{
    unsigned int metoda: 2;
    unsigned int n: 10;
    unsigned int li: 1;
    unsigned int ls: 3;
    unsigned int i: 3;
};

double f0(double);
double f1(double);
double f2(double);
double f3(double);
double f4(double);
double integralaTrapez(double a, double b, unsigned int n, double (*f)(double));
double integralaDreptunghi(double a, double b, unsigned int n, double (*f)(double));
double integralaSimpson(double a, double b, unsigned int n, double (*f)(double));

struct Optiuni analiza(int argc, char**argv);

double calcul(struct Optiuni op, double (*integrale[5])(double));

#endif
