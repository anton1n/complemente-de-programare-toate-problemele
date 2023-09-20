#include "Header.h"

double **citireMatrice(FILE *f,int l, int c)
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
			//printf("M[%d][%d] = ",i,j);
			fscanf(f,"%lf", &m[i][j]);
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

char *meniu(struct MENU_ITEM *meniu, struct MATRICE *M)
{
    int i, op=1;
    char *filename =0;
    char *input_file=0;
    FILE *f=0;
    puts("Alegeti una sau mai multe optiuni");
    for(i=0;i<3;++i)
    {
        printf("\n%d)", i+1);
        printf("%s", meniu[i].nume);
    }

    while(op)
    {
        puts("\nIntroduceti optiunea dorita: ");
        scanf("%d", &op);
        meniu[op-1].select = 1;
        
        puts("Doriti sa continuati? 1/0");
        scanf("%d",&op);
    }

    puts("Introduceti fisierul de intrare: ");
    input_file = (char*)malloc(20);
    scanf("%s", input_file);

    f = fopen(input_file, "r");
    fscanf( f, "%d", &M->l );
    fscanf( f, "%d", &M->c );
    M->m = citireMatrice(f, M->l, M->c );

    puts("Doriti sa afisati intr-un fisier? 1/0");
    scanf("%d", &op);
    if(op)
    {
        filename = (char*)malloc(20);
        scanf("%s", filename);
    }

    return filename;
}
typedef struct thread_info THREAD_INFO;
void * threadMain( void * arg )
{
	int should_run = 1;
	THREAD_INFO *ptr_tinfo = (THREAD_INFO *) arg;

	printf( "Thread [ %d ] activ\n", ptr_tinfo->thread_num );

	while( 1 == should_run )
	{
		pthread_mutex_lock( &( ptr_tinfo->m ) );
		// printf( "after mutex\n" );
		while( 0 == ptr_tinfo->status )
		{
			pthread_cond_wait( &( ptr_tinfo->self ), &( ptr_tinfo->m ) );
		}
		// printf( "after cond\n" );
		if( -1 == ptr_tinfo->status )
		{
			should_run = 0;
			pthread_mutex_unlock( &( ptr_tinfo->m ) );
			continue;
		}
		printf( "Thread [ %d ] start %s\n", ptr_tinfo->thread_num, ptr_tinfo->norm->nume);
		ptr_tinfo->result = ptr_tinfo->norm->pf(ptr_tinfo->mat->m, ptr_tinfo->mat->l, ptr_tinfo->mat->c);
		ptr_tinfo->status = 0;
		pthread_mutex_unlock( &( ptr_tinfo->m ) );

		pthread_cond_signal( &( ptr_tinfo->parent ) );
	}

	printf( "Thread [ %d ] a terminat!\n", ptr_tinfo->thread_num );
    //printf("%d:  %lf ",ptr_tinfo->thread_num, (ptr_tinfo )->result);

    

	return NULL;
}


void * afisare( void * arg)
{
    THREAD_INFO *ptr_tinfo = (THREAD_INFO *) arg;
    int iter=0;
    FILE *file =0;
    if(ptr_tinfo->filename)
    {
        file = fopen(ptr_tinfo->filename, "w");
    }

    if(!ptr_tinfo->filename)
    {
        if((ptr_tinfo+iter)->norm->select)
            printf("%lf ", (ptr_tinfo+iter)->result);
    }
            
    else
        {
            if((ptr_tinfo+iter)->norm->select)
                fprintf(file, "%lf ", (ptr_tinfo+iter)->result);
        }

    return NULL;
}
void resetMemory( void * block_address, int count, long unsigned int esize )
{
	memset( block_address, 0x00, esize * count );
}