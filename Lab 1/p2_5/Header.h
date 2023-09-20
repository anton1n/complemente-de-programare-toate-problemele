#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(x, y) (((x) > (y)) ? (x): (y))

struct MENU_ITEM{
	char *nume;
	double (*f)(double **a, int l, int c);
};

double **citireMatrice(int l, int c); 
void afisareMatrice(double **a, int l, int c);
double norma1(double **a, int l, int c);
double norma2(double **a, int l, int c);
double normaEuclidiana(double **a, int l, int c);
int menu(struct MENU_ITEM meniu[], unsigned int nf, char *msg);

#endif
