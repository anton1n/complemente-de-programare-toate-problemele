#include "Header.h"

int main(void)
{
	struct Rez rezultat;

	rezultat = identificare(5, 1, 2, 3, 4, 5) ;


	puts("cresc desc scresc    sdesc    nmare    nmic    constant erroare");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", rezultat.cresc, rezultat.desc, rezultat.scresc, rezultat.sdesc, rezultat.nmare, rezultat.nmic, rezultat.constant, rezultat.err);

	return 0;
}
