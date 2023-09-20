#include "Header.h"


int main(void)
{
    int i, rcode;
    pthread_attr_t attr;
    struct MATRICE *M = (struct MATRICE *)malloc(sizeof(struct MATRICE));
    struct MENU_ITEM *menu = malloc(3 * sizeof(struct MENU_ITEM));
    struct thread_info *tinfo = (struct thread_info*)calloc(3, sizeof(struct thread_info) );

    menu[0] = (struct MENU_ITEM){"Calculul normei 1", norma1, 0};
    menu[1] = (struct MENU_ITEM){"Calculul normei infinit", norma2, 0};
    menu[2] = (struct MENU_ITEM){"Calculul normei euclidiene", normaEuclidiana, 0};

    char *filename;
    //FILE *file;
    
    filename = meniu(menu, M);
    //if(filename)
    //{
    //    file = fopen(filename, "w");
    //}
    //afisareMatrice(M->m, M->l, M->c);
    //printf("%d", menu[0].select);

    rcode = pthread_attr_init(&attr);
    if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la initializarea atributelor pentru thread-uri\n" );
		exit(-1);
	}
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED );

    for(i=0;i<3;++i)
    {
        (tinfo + i)->norm = menu + i;
        (tinfo + i)->mat = M;
        (tinfo + i)->filename = filename;
        (tinfo + i)->thread_num = i;
    	( tinfo + i )->status = 0;
        (tinfo + i)->result =0;
		( tinfo + i )->self = ( pthread_cond_t ) PTHREAD_COND_INITIALIZER;
		( tinfo + i )->parent = ( pthread_cond_t ) PTHREAD_COND_INITIALIZER;
		( tinfo + i )->m = ( pthread_mutex_t ) PTHREAD_MUTEX_INITIALIZER;

        rcode = pthread_create( &((tinfo + i)->thread_id), &attr, &threadMain, (void*)(tinfo + i) );
        if( 0!= rcode)
        {
            fprintf( stderr, "Eroare la crearea thread-ului logic %d\n", i );
            memset(tinfo, 0, 3*sizeof(struct thread_info));
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

    int iter;
    for(   iter = 0; iter < 3; ++iter )
	{
		pthread_mutex_lock( &(( tinfo + iter )->m ) );
		( tinfo + iter )->status = 1;
		pthread_mutex_unlock( &(( tinfo + iter)->m ) );

		pthread_cond_signal( &(( tinfo + iter )->self ) );
	}

    int split_iter = iter;
	while( split_iter < 3 )
	{
		for( iter = 0; iter < 3 ; ++iter )
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

	for( iter = 0; iter < 3; ++iter )
	{
		pthread_mutex_lock( &(( tinfo + iter )->m ) );
		while( 1 == ( tinfo + iter )->status )
		{
			pthread_cond_wait( &(( tinfo + iter )->parent ), &(( tinfo + iter )->m ) );
		}
		( tinfo + iter )->status = -1;
		pthread_mutex_unlock( & (( tinfo + iter )->m ) );

		pthread_cond_signal( &(( tinfo + iter )->self ) );
	}

    

    for( iter = 0; iter < 3; ++iter )
	{
        
		pthread_cond_destroy( &(( tinfo + iter )->self ) );
		pthread_cond_destroy( &(( tinfo + iter )->parent ) );
		pthread_mutex_destroy( &(( tinfo + iter )->m ) );
	}

    pthread_t thread[3];

    for(i =0;i<3;++i)
    {
        pthread_create(&thread[i], NULL, &afisare, (void*)(tinfo +i));
    }

    pthread_exit(NULL);

    resetMemory( ( void * ) tinfo, 3, sizeof( struct thread_info ) );
    free( ( void * ) tinfo );
	tinfo = 0;

    for(i=0;i<M->l;++i)
    {
        resetMemory((void*)M->m,M->c,sizeof(double));
    }
    free(M->m);
    M->m=0;
    
    resetMemory((void*)menu, 3,sizeof(struct MENU_ITEM));
    free(menu);
    menu=0;

    return 0;
}