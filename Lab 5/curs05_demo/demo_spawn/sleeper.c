#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc, char* argv [] )
{
	int iter;
	printf( "Hello world from child process!\n" );
	for( iter=0; iter<argc; ++iter )
	{
		printf( "arg no: %3d\tvalue: %s\n", iter, argv[iter] );
	}

	for( iter=0; iter<60; ++iter )
	{
		printf( "%3d second%c\n", iter+1, ( iter==0 ? ' ': 's' ) );
		sleep( 1 );
	}

	return 0;
}
