#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct thread_info{
    pthread_t thread_id;
    int *v1;
    int *v2;
    int thread_num;
    int size;
    int partial_result;
};

typedef struct thread_info THREAD_INFO;


int **m1=0, **m2=0;

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

int *returnColumn(int **m, int l, int c)
{
    int iter;
    int *v = (int*)calloc(c,sizeof(int));
    //--c;
    for(iter =0; iter<l;++iter)
    {
        v[iter] = m[iter][c];
    }

    return v;
}

void rotateMatrix(int **matrix, int l, int c)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = i; j<c; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c/2; j++) 
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][2-j];
            matrix[i][2-j] = temp;
        }
    }
}

void invertLines(int **matrix, int l, int c)
{
    for (int i = 0; i < l/2; i++) 
    {
        for (int j = 0; j < c; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[2-i][j];
            matrix[2-i][j] = temp;
        }
    }
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

    m1 = readMatrixFromFile(input1, l1, c1);
    m2 = readMatrixFromFile(input2, l2, c2);

    fclose(input1);
    input1 = 0;
    fclose(input2);
    input2=0;

    num_threads = l1 * c2 ;
    
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

    int j=0;

    for(iter =0; iter<num_threads; ++iter)
    {
        
        (tinfo + iter )->thread_num = iter+1;
        (tinfo + iter)->v1 = returnColumn(m1, l1, j);
        (tinfo + iter)->v2 = m2[iter%c1];
        (tinfo + iter )->size = c1;
        rcode = pthread_create( &(( tinfo + iter )->thread_id), &attr, &dotProduct, tinfo + iter );
        //printf("\n _%d_ %d_%d_\n", j, iter%c1, (tinfo + iter )->thread_num);
        if( 0 != rcode )
		{
			fprintf( stderr, "Eroare la crearea thread-ului %d\n", iter + 1 );
			exit( EXIT_FAILURE );
		}

        if((iter+1) % c2 == 0)
        {
            ++j;
        }
    }

    rcode = pthread_attr_destroy( & attr );
	if( 0 != rcode )
	{
		fprintf( stderr, "Eroare la distrugerea attr\n" );
		exit( EXIT_FAILURE );
	}

    int ** matrix_result = 0;

	matrix_result = ( int ** ) calloc( l1, sizeof( int *) );
    for(iter = 0; iter<l1;++iter)
    {
        matrix_result[iter] = (int*)calloc(c2,sizeof(int));
    }

	if( NULL == matrix_result )
	{
		fprintf( stderr, "Nu pot aloca memorie " );
		exit( EXIT_FAILURE );
	}
    for( iter = 0 ;iter <num_threads; ++iter)
    {
        
        rcode = pthread_join( (tinfo + iter)->thread_id, NULL );
        if( 0 != rcode )
		{
			fprintf( stderr, "Eroare la sincronizare\n" );
			exit( EXIT_FAILURE );
		}
        int row = iter / 3;
        int col = iter % 3;
        matrix_result[row][col] = (tinfo + iter)->partial_result;

    }

    rotateMatrix(matrix_result, l1, c2);
    invertLines(matrix_result, l1, c2);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", matrix_result[i][j]);
        }
        printf("\n");
    }
 

    resetMemory( ( void * ) tinfo, num_threads, sizeof( THREAD_INFO ) );
	free( tinfo );
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
        resetMemory((void *) matrix_result, c2, sizeof(int));
    }

    matrix_result =0;
    m1 = 0;
    m2 =0;
    free(m1);
    free(m2);
    free(matrix_result);

    return 0;
}