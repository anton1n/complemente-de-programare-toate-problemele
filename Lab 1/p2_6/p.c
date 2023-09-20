#include "Header.h"

int main(void)
{
    unsigned int op;
    POLIGON a, b;
    unsigned int nrPct;

    struct MENU_ITEM meniu[]={
    {"Euclidiana ", dEuclidiana},
    {"Manhattan", dManhattan},
    {"Minkovski", dMinkovski3}
    };

    //primul poligon
    a.nume="Triunghi";

    a.p = (PUNCT*)malloc(3*sizeof(PUNCT));
    a.p[0].x = 1;
    a.p[0].y = 5;
    a.p[1].x = 1;
    a.p[1].y = 1;
    a.p[2].x = 5;
    a.p[2].y = 5;

    a.p[0].distanta = meniu[0].f;
    a.Aria = ariaTriunghi;

    a.Perimetru = perimetruPoligon;

    calcule(a,3);
    afisareValoriPoligon(a);

    //al doilea poligon
    printf("Introduceti nr de puncte: \n");
    scanf("%u", &nrPct);

    op = menu(meniu,3,"Alegeti metoda de calcul a distantei: \n");
    init_poligon(&b,nrPct, meniu[op-1].f);

    calcule(b,nrPct);
    afisareValoriPoligon(b);

    return 0;
}
