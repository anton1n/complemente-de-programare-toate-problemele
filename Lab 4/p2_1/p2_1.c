//exemplu linie comanda: ./p2_1 input1.txt input2.txt 3
//pentru un rezeltat corect e preferebil ca:  nr elemete ale matricei % nr de treaduri ales  == 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct thread_info{
    pthread_t thread_id;
    int start, end;
    int status;
    int thread_num;
    int l;
    int c;
    pthread_cond_t self;
    pthread_cond_t parent;
    pthread_mutex_t m;
};

typedef struct thread_info THREAD_INFO;


int **m1=0, **m2=0;
int **C=0;

int ** readMatrixFromFile( FILE *input, int l, int c )
{
	int ** result = 0, iter, j;

	result = ( int ** ) calloc( l, sizeof( int *) );
    for(iter = 0; iter<l;++iter)
    {
        result[iter] = (int*)calloc(c,sizeof(int));
    }

	if( NULL == result )
	{
		fprintf( stderr, "Nu pot aloca memorie " );
		exit( EXIT_FAILURE );
	}

	for(iter =0;iter<l;++iter)
    {
        for(j =0;j<c;++j)
        {
            fscanf(input, "%d", &result[iter][j]);
        }
    }

	return result;
}

void resetMemory( void * block_address, int count, long unsigned int esize )
{
	memset( block_address, 0x00, esize * count );
}


int multiply(void *arg) 
{
    THREAD_INFO *ptr_tinfo = (THREAD_INFO *) arg;

    int start_row = ptr_tinfo->start;
    int end_row = ptr_tinfo->end;
    int n = ptr_tinfo->l;
    int p = ptr_tinfo->c;


    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < p; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += m1[i][k] * m2[k][j];
            }
            C[i][j] = sum;
        }
    }
    return 0;
}

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
		printf( "Thread [ %d ] start de la %d la %d\n", ptr_tinfo->thread_num, ptr_tinfo->start, ptr_tinfo->end);
		multiply( (void*)(ptr_tinfo));
		ptr_tinfo->status = 0;
		pthread_mutex_unlock( &( ptr_tinfo->m ) );

		pthread_cond_signal( &( ptr_tinfo->parent ) );
	}

	printf( "Thread [ %d ] a terminat!\n", ptr_tinfo->thread_num );

	return NULL;
}


int main(int argc, char **argv)
{
    int l1, c1 ,l2, c2, iter;
    FILE *input1=0, *input2=0;
    char *file_name1 = argv[1], *file_name2 = argv[2];
    int num_threads, rcode;
    pthread_attr_t attr;
    THREAD_INFO *tinfo = 0;

    input1 = fopen(file_name1, "r");
    input2 = fopen(file_name2, "r");
    
    if(NULL == input1 || NULL == input2)
    {
        fprintf( stderr, "Nu pot deschide fisierele de intrare!\n" );
		exit( EXIT_FAILURE );
    }

    fscanf( input1, "%d", &l1 );
    fscanf( input1, "%d", &c1 );

    fscanf( input2, "%d", &l2 );
    fscanf( input2, "%d", &c2 );

    if(c1!=l1)
    {
        puts("Nu se poate efectua inmultirea! ");
        exit(1);
    }

    C = ( int ** ) calloc( l1, sizeof( int *) );
    for(iter = 0; iter<l1;++iter)
    {
        C[iter] = (int*)calloc(c2,sizeof(int));
    }

	if( NULL == C )
	{
		fprintf( stderr, "Nu pot aloca memorie " );
		exit( EXIT_FAILURE );
	}

    m1 = readMatrixFromFile(input1, l1, c1);
    m2 = readMatrixFromFile(input2, l2, c2);

    fclose(input1);
    input1 = 0;
    fclose(input2);
    input2=0;

    num_threads = atoi(argv[3]);
    
    rcode = pthread_attr_init( &attr );
	if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la inializarea attr\n" );
		exit( EXIT_FAILURE );
	}

	tinfo = ( struct thread_info * ) calloc( num_threads, sizeof( struct thread_info ) );
	if( NULL == tinfo )
	{
		fprintf( stderr, "Eroare la alocare info\n" );
		exit( EXIT_FAILURE );
	}

    int split = (l1*c2 )/ num_threads;

    rcode = pthread_attr_init( &attr );
	if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la initializarea atributelor pentru thread-uri\n" );
		exit(-1);
	}
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );

	tinfo = ( THREAD_INFO * ) malloc( num_threads * sizeof( THREAD_INFO ) );
	if( NULL == tinfo )
	{
		fprintf( stderr, "Eroare la alocarea vectorului tinfo\n" );
		exit(-1);
	}

    for(iter = 0; iter< num_threads; ++iter)
    {
        ( tinfo + iter )->thread_num = iter;
        ( tinfo + iter )->start = (l1/num_threads)*iter;
        ( tinfo + iter )->end = (l1/num_threads)*(iter+1);
        ( tinfo + iter )->l = l1;
        ( tinfo + iter )-> c = c2;
		( tinfo + iter )->status = 0;
		( tinfo + iter )->self = ( pthread_cond_t ) PTHREAD_COND_INITIALIZER;
		( tinfo + iter )->parent = ( pthread_cond_t ) PTHREAD_COND_INITIALIZER;
		( tinfo + iter )->m = ( pthread_mutex_t ) PTHREAD_MUTEX_INITIALIZER;

        rcode = pthread_create( &((tinfo + iter)->thread_id), &attr, &threadMain, (void*)(tinfo+iter) );
        if( 0 != rcode )
		{
			fprintf( stderr, "Eroare la crearea thread-ului logic %d\n", iter );
			resetMemory( ( void * ) tinfo, num_threads, sizeof( THREAD_INFO ) );
			free( ( void * ) tinfo );
			tinfo = 0;
			pthread_attr_destroy( & attr );
			exit(-1);
		}

    }

    rcode = pthread_attr_destroy( &attr );
	if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la distrugerea structurii attr\n" );
		exit(-1);
	}

    for( iter = 0; iter < num_threads; ++iter )
	{
		pthread_mutex_lock( &(( tinfo + iter )->m ) );
		( tinfo + iter )->status = 1;
		pthread_mutex_unlock( &(( tinfo + iter)->m ) );

		pthread_cond_signal( &(( tinfo + iter )->self ) );
	}

    int split_iter = iter;
	while( split_iter < split )
	{
		for( iter = 0; iter < num_threads && split_iter < split; ++iter )
		{
			pthread_mutex_lock( &(( tinfo + iter )->m ) );
			while( 1 == ( tinfo + iter )->status )
			{
				pthread_cond_wait( &(( tinfo + iter )->parent ), &(( tinfo + iter )->m ) );
			}
			( tinfo + iter )->status = 1;
			pthread_mutex_unlock( &(( tinfo + iter )->m ) );
			
			++split_iter;

			pthread_cond_signal( &(( tinfo + iter )->self ) );
		}
	}

	for( iter = 0; iter < num_threads; ++iter )
	{
		pthread_mutex_lock( &(( tinfo + iter )->m ) );
		while( 1 == ( tinfo + iter )->status )
		{
			pthread_cond_wait( &(( tinfo + iter )->parent ), &(( tinfo + iter )->m ) );
		}
		( tinfo + iter )->status = -1;
		pthread_mutex_unlock( &(( tinfo + iter )->m ) );

		pthread_cond_signal( &(( tinfo + iter )->self ) );
	}



    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
 
    	// clean-up
	for( iter = 0; iter < num_threads; ++iter )
	{
		pthread_cond_destroy( &(( tinfo + iter )->self ) );
		pthread_cond_destroy( &(( tinfo + iter )->parent ) );
		pthread_mutex_destroy( &(( tinfo + iter )->m ) );
	}
	resetMemory( ( void * ) tinfo, num_threads, sizeof( THREAD_INFO ) );
	free( ( void * ) tinfo );
	tinfo = 0;

    for(iter = 0;iter< l1;++iter)
    {
        resetMemory((void *) m1, c1, sizeof(int));
    }
    
    for(iter = 0;iter< l2;++iter)
    {
        resetMemory((void *) m2, c2, sizeof(int));
    }

     for(iter = 0;iter< l1;++iter)
    {
        resetMemory((void *) C, c2, sizeof(int));
    }

    C =0;
    m1 = 0;
    m2 =0;
    free(m1);
    free(m2);
    free(C);


    return 0;
}