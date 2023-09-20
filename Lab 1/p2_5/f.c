#include "Header.h"


double **citireMatrice(int l, int c)
{
	int i, j;
	double **m = (double**)malloc(l*sizeof(double*));
	
	for(i=0;i<l;++i)
	{
		m[i] = (double*)malloc(c*sizeof(double));
	}
	
	for(i=0;i<l;++i)
	{
		for(j=0;j<c;++j)
		{
			printf("M[%d][%d] = ",i,j);
			scanf("%lf", &m[i][j]);
		}
	}
	return m;
}

void afisareMatrice(double **a, int l, int c)
{
	int i, j;

	for(i=0;i<l;++i)
	{
		for(j=0;j<c;++j)
		{
			printf(" %.2lf ",a[i][j]);
		}
		puts("\n");
	}

}
double norma2(double **a, int l, int c)
{
	int i, j;
	double maxim= -1, sum;

	for(i=0;i<l;++i)
	{
		sum = 0;
		for(j=0;j<c;++j)
		{
			sum += abs(a[i][j]);
		}

		maxim = max(maxim,sum);
	}
	return maxim;
}

double norma1(double **a, int l, int c)
{
	int i, j;
	double maxim= -1, sum;

	for(i=0;i<l;++i)
	{
		sum = 0;
		for(j=0;j<c;++j)
		{
			sum += abs(a[j][i]);
		}

		maxim = max(maxim,sum);
	}
	return maxim;

}

double normaEuclidiana(double **a, int l, int c)
{
	int i, j;
	double sum = 0;

	for(i=0;i<l;++i)
	{
		for(j=0;j<c;++j)
		{
			sum += (a[i][j])*(a[i][j]);
		}

	}
	return sqrt(sum);
}

int menu(struct MENU_ITEM meniu[], unsigned int nf, char *msg)
{
	int optiune;
	register unsigned int i;
	puts(msg);
	for(i=0;i<nf;++i)
	{
		printf("\t%d - %s\n", i+1, meniu[i].nume);
	}
	printf("\t >> ");
	scanf("%d", &optiune);
	return optiune;
}

