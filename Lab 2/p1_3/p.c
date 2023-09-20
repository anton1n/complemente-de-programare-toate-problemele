#include "Header.h"

int main(void)
{
	union Rezultat rezultat;

	/*
	rezultat = functie("media aritmetica", 3, 1, 2, 3);
	printf("%lf\n", rezultat.d);
	
	rezultat = functie("media geometrica", 3, 1, 2, 3);
	printf("%lf\n", rezultat.d);

	rezultat = functie("minim", 3, 1, 2, 3);
	printf("%d\n", rezultat.i);

	rezultat = functie("maxim", 3, 1, 2, 3);
	printf("%d\n", rezultat.i);
*/
	char prelucrare[10];
	puts("Introduceti prelucrarea dorita: ");
	scanf("%[^\n]%*c", prelucrare);
	//fgets(prelucrare,10,stdin);
	rezultat = functie(prelucrare, 3, 1, 2, 3);
	printf("%lf %d\n", rezultat.d, rezultat.i);

	return 0;
}
