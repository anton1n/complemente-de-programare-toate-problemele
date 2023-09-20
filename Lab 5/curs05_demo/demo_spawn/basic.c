#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main( int argc, char* argv [] )
{
	int iter;
	pid_t own_pid = getpid( );
	pid_t parent_pid = getppid( );
	printf( "Hello world from child process: pid %jd/parent pid %jd!\n", (intmax_t) own_pid, (intmax_t) parent_pid );
	for( iter=0; iter<argc; ++iter )
	{
		printf( "arg no: %3d\tvalue: %s\n", iter, argv[iter] );
	}
	return 0;
}
