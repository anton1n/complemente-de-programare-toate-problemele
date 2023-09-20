#include <stdio.h>
#include "Header.h"

int main(void)
{
    unsigned int n;
    double integrala;

    printf("n =");
    scanf("%u", &n);

    integrala = integralaTrapez(2,3,n,f);

    printf("Integrala de la 2 la 3 este: %lf", integrala);

    return 0;
}
