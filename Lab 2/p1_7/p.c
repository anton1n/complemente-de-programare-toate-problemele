#include "Header.h"

int main(int argc, char **argv)
{
    //printf("%s\n", argv[1]);
    double (*I[5])(double);
    struct Optiuni op ;

    op = analiza(argc, argv);

    printf("%d %d %d %d %d\n", op.metoda, op.n, op.li, op.ls, op.i);

    I[0] = f0;
	I[1] = f1;
	I[2] = f2;
	I[3] = f3;
	I[4] = f4;

    double rezultat = calcul(op, I);

    printf("%lf", rezultat);


    return 0;
}
