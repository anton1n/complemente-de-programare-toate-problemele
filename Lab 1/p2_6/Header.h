#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _PUNCT{
	double x, y;
	double (*distanta)(struct _PUNCT, struct _PUNCT);
}PUNCT;

typedef struct _POLIGON{
	unsigned int n;

	struct _PUNCT *p;
	char *nume;
	double aria;
	double perimetru;
	double (*Aria)(struct _PUNCT *, unsigned int);
	double (*Perimetru)(struct _PUNCT *, unsigned int);
}POLIGON;

struct MENU_ITEM{
	char *nume;
	double (*f)( PUNCT a, PUNCT b);
};


double dEuclidiana( PUNCT a, PUNCT b);
double dManhattan( PUNCT a, PUNCT b);
double dMinkovski3( PUNCT a, PUNCT b);
double ariaTriunghi(PUNCT *a, unsigned int nr);
double ariaPlus(PUNCT *a, unsigned int nr);
double perimetruPoligon(PUNCT *a, unsigned int nr);
void init_punct(PUNCT *a);
void init_poligon(POLIGON *a, unsigned int n, double (*pf)(struct _PUNCT a, struct _PUNCT b) );
void afisareValoriPoligon(POLIGON a);
void dealocare(POLIGON a);
int menu(struct MENU_ITEM meniu[], unsigned int nf, char *msg);

#define calcule(a, n)\
do { \
    a.aria = a.Aria(a.p, n); \
    a.perimetru = a.Perimetru(a.p, n); \
} while (0)


#endif
