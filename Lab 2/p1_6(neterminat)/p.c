#include "Header.h"

int main(int argc, char **argv)
{
    POLIGON a;
    struct Optiuni op;

    op = analiza(argc, argv);

    printf("Introduceti nr de puncte: \n");
    scanf("%u", &nrPct);

    init_poligon(&b, nrPct, op.metoda );

}
