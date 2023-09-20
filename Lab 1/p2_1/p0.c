#include <stdio.h>
#include <math.h>
#include "operatii.h"

int main(void)
{
	int a, b;		//Datele de intare
	double ma, mg;	//Rezultatele
					
	help();
/*
 * Citesc datele de intrare
 */
	do {
		printf("Introduceti doua numere întregi ");
		printf("(ambele pozitiva sau ambele negative):\n");
		printf("a = ");
		scanf("%d", &a);
		printf("b = ");
		scanf("%d", &b);
	} while (a * b < 0);
/*
 * Calculez cele două medii
 */
	ma = mediaAritmetica(a, b);
	mg = mediaGeometrica(a, b);
/*
 * Afisez rezultatele
 */
	puts("");
	printf("Media aritmetica a numerelor %d și %d este %.2lf\n", a, b, ma);
	printf("Media geometrica a numerelor %d și %d este %.2lf\n", a, b, mg);

	return 0;
}

