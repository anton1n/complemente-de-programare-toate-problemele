#include "Header.h"

double dEuclidiana( PUNCT a, PUNCT b)
{
	return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

double dManhattan( PUNCT a, PUNCT b)
{
	return (abs(a.x-b.x) + abs(a.y-b.y));
}

double dMinkovski3( PUNCT a, PUNCT b)
{
	return pow((pow(abs(a.x-b.x),3) + pow(abs(a.y-b.y),3)),1/3);
}

double ariaTriunghi(PUNCT *a, unsigned int nr)
{
	double ab, bc, ac, sp;

	ab = a[0].distanta(a[0],a[1]);
	bc = a[0].distanta(a[1],a[2]);
	ac = a[0].distanta(a[0],a[2]);
	
	sp = (ab + bc + ac)/2;

	return sqrt(sp*(sp-ab)*(sp-bc)*(sp-ac));

}
double ariaPlus(PUNCT *a, unsigned int nr)
{
	int i, k=1;
	double ab, bc, ac, sp;
	double aria=0;

	//vor fi nr-2 triunghiuri

	for(i=0;i<nr-2;++i)
	{
		ab = a[0].distanta(a[0],a[k]);
		bc = a[0].distanta(a[k],a[k+1]);
		ac = a[0].distanta(a[0],a[k+1]);
		sp = (ab + bc + ac)/2;

		aria+= sqrt(sp*(sp-ab)*(sp-bc)*(sp-ac));

		++k;
	}
	return aria;
}
double perimetruPoligon(PUNCT *a, unsigned int nr)
{
	int i;
	double perimetru = 0;

	for(i=0;i<nr-1;++i)
	{
		perimetru+=a[0].distanta(a[i],a[i+1]);
	}
	perimetru+=a[0].distanta(a[0],a[nr-1]);
	return perimetru;
}
void init_punct(PUNCT *a)
{
	puts("Introduceti coordonate punct\n");

	scanf("%lf", &a->x);
	scanf("%lf",&a->y);
}
void init_poligon(POLIGON *a, unsigned int n, double(*pf)(struct _PUNCT a, struct _PUNCT b) )
{
	int i;

	puts("Introduceti date poligon: \n");
	
	puts("Introduceti numele: ");
	char name[20];
	scanf("%s",name);
	a->nume = malloc(sizeof(name)*sizeof(char));
	strcpy(a->nume, name);
	//a->nume = name;
	//scanf("%s",a->nume);

	puts("Inttroduceti punctele poligonului: ");

	a->p = malloc(n*sizeof(PUNCT));
	PUNCT *pp = (PUNCT*)malloc(n*sizeof(PUNCT));
	for(i=0;i<n;++i)
	{

		init_punct(pp);
		a->p[i].x = pp->x;
		a->p[i].y = pp->y;

		//init_punct(a->p[0]);
	}
	a->Perimetru = perimetruPoligon;
	a->p[0].distanta = pf;
	if(n==3)
		a->Aria = ariaTriunghi;
	else
		a->Aria = ariaPlus;
}
void afisareValoriPoligon(POLIGON a)
{
	printf("Nume: %s\n", a.nume);
	printf("Aria: %.2lf\n",a.aria);
	printf("Perimetru: %.2lf", a.perimetru);
	puts("\n");
}

struct Optiuni analiza(int argc, char**argv)
{
	struct Optiuni op;

	if(argc ==1 )
	{
		op.metoda = 0;
		return op;
	}

	if(strcmp(argv[1],"-e")==0)
	{
		op.metoda  = 0;
	}
	else if(strcmp(argv[1], "-m")==0)
	{
		op.metoda = 1;
	}
	else if(strcmp(argv[1], "-mo")==0)
	{
		op.metoda = 2;
	}

	return op;
}

double calcul(int c, ...)
{
	switch(c)
	{
		case int("t"):
			return ariaTriunghi();
			break;
		case int("d"):
			return ariaDreptunghi();
			break;
		case int("p"):
			return ariaParalelogram();
			break;
		case int("g"):
			return ariaPoligon();
			break;
		default:
			return -1;
			break;
	}


}
