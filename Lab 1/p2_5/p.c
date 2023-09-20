#include "Header.h"

int main(void)
{
	int l, c;
	double **m;
	unsigned int op;

	puts("Intreoduceti numarul de linii si numarul de coloane al matricei dorite: \n");
	scanf("%d",&l);
	scanf("%d",&c);
	
	m = citireMatrice(l,c);
	afisareMatrice(m,l,c);

	struct MENU_ITEM meniu[]={
		{"Calculul normei 1", norma1},
		{"Calculul normei infinit", norma2},
		{"Calculul normei euclidiene", normaEuclidiana}
	};

	op = menu(meniu,3,"Posibilitatile sunt: \n");

	printf("%s \n", meniu[op-1].nume);
	printf("%lf", meniu[op-1].f(m,l,c));

	return 0;
}
