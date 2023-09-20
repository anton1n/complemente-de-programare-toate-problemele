#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

#include <string.h>

int *vec1=0, *vec2=0;

struct thread_info{
    pthread_t thread_id;
    int *v1;
    int *v2;
    int thread_num;
    int size;
    int partial_result;
};

typedef struct thread_info THREAD_INFO;

int * readVectorFromFile( FILE *input, int count )
{
	int * result = 0, iter;
	result = ( int * ) calloc( count, sizeof( int ) );
	if( NULL == result )
	{
		fprintf( stderr, "Nu pot aloca memorie [%lu octeti]\n", count * sizeof( int ) );
		exit( EXIT_FAILURE );
	}

	for( iter = 0; iter < count; ++iter )
	{
		fscanf( input, "%d", result + iter );
	}

	return result;
}

void resetMemory( void * block_address, int count, long unsigned int esize )
{
	memset( block_address, 0x00, esize * count );
}

void *dotProduct( void *arg)
{
    THREAD_INFO *ptr_tinfo = (THREAD_INFO *) arg;
    int result = 0, iter;
	int *vec1 = ptr_tinfo->v1;
    int *vec2 = ptr_tinfo->v2;
    int size = ptr_tinfo->size;

	for( iter = 0; iter < size ;++iter )
	{
		result += *( vec1 + iter ) * *( vec2 + iter );
	}

    ptr_tinfo->partial_result = result;
    return NULL;

}


int main(int argc, char **argv)
{
    int count, num_threads, partition, iter;
    FILE *input_file = 0;

    if( 3 != argc )
	{
		fprintf( stderr, "Argumente obligatorii: file, number of threads/n" );
		exit( EXIT_FAILURE );
	}

    char *file_name = argv[1];
    input_file = fopen(file_name, "r");

    if(NULL == input_file)
    {
        fprintf( stderr, "Nu pot deschide fisierul de intrare!\n" );
		exit( EXIT_FAILURE );
    }

    num_threads = atoi(argv[2]);

    fscanf( input_file, "%d", &count );
    printf("\n%d\n", count);

    vec1 = readVectorFromFile(input_file, count);
    vec2 = readVectorFromFile(input_file, count);

    fclose(input_file);
    input_file = 0;

    partition = count / num_threads;

    printf("\n%d\n", partition);

    pthread_attr_t attr;
    int rcode;
    THREAD_INFO *tinfo = 0;

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

    for(iter =0; iter<num_threads; ++iter)
    {
        (tinfo + iter )->thread_num = iter+1;
        (tinfo + iter)->v1 = vec1 + iter* partition;
        (tinfo + iter)->v2 = vec2 + iter * partition;
        (tinfo + iter )->size = partition;
        rcode = pthread_create( &(( tinfo + iter )->thread_id), &attr, &dotProduct, tinfo + iter );

        if( 0 != rcode )
		{
			fprintf( stderr, "Eroare la crearea thread-ului %d\n", iter + 1 );
			exit( EXIT_FAILURE );
		}
    }

    rcode = pthread_attr_destroy( & attr );
	if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la distrugerea attr\n" );
		exit( EXIT_FAILURE );
	}

    int total = 0;
    for( iter = 0; iter < num_threads; ++iter)
    {
        printf("\n%d\n", (tinfo + iter)->partial_result);
        rcode = pthread_join( (tinfo + iter)->thread_id, NULL );
        if( 0 != rcode )
		{
			fprintf( stderr, "Eroare la sincronizare\n" );
			exit( EXIT_FAILURE );
		}
        total += (tinfo + iter)->partial_result;
    }

    
    printf("Rezultat: %d", total);
 

    resetMemory( ( void * ) tinfo, count, sizeof( THREAD_INFO ) );
	free( tinfo );
	tinfo = 0;
    resetMemory( ( void * ) vec1, count, sizeof( int ) );
    resetMemory( ( void * ) vec2, count, sizeof( int ) );
    free(vec1);
    free(vec2);

    return 0;

}