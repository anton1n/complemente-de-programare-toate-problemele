#include "Header.h"

int main(void)
{

	unsigned int n , op;

	printf("n = ");
	scanf("%u", &n);

	struct MENU_ITEM meniu[]={
		{"Calculul integralei prin metoda trapezelor", integralaTrapez},
		{"Calculul integralei prin metoda dreptunghiurilor", integralaDreptunghi},
		{"Calculul integralei prin metoda Simpson", integralaSimpson}
	};
	op = menu(meniu,3,"Posibilitatile sunt:\n");

	printf("%s \n",meniu[op - 1].nume);
	printf("%lf",meniu[op-1].f(2,3,n,f));

	return 0;
}
