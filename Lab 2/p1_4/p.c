#include "Header.h"

int main(void)
{
	union Rezultat rezultat;

	char prelucrare[10];
	puts("Introduceti prelucrarea dorita: ");
	scanf("%[^\n]%*c", prelucrare);
	//fgets(prelucrare,10,stdin);
	rezultat = functie(prelucrare, 1, 2, 3, 0);
	printf("%lf %d\n", rezultat.d, rezultat.i);

	return 0;
}
