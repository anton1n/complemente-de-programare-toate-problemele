#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <errno.h>

#include <unistd.h>
#include <signal.h>

#include <string.h>
#include <fcntl.h>

//#include <sys/_types.h>
#include <sys/stat.h>

void print_error( int e_num, char* e_msg )
{
	errno = ( -1 == e_num ? errno : e_num ) ;
	perror( e_msg );
	exit( EXIT_FAILURE );
}

int main( int argc, char* argv [] )
{
	int iter;
	int f_code, fd;
	char string[128];
	pid_t own_pid = getpid( );
	pid_t parent_pid = getppid( );
	printf( "Hello world from child process: pid %jd/parent pid %jd!\n", (intmax_t) own_pid, (intmax_t) parent_pid );

	for( iter=0; iter<argc; ++iter )
	{
		printf( "arg no: %3d\tvalue: %s\n", iter, argv[iter] );
	}
	puts(argv[1]);
	f_code = mkfifo( argv[1], 0666 );
	if( 0 != f_code )
	{
		if( EEXIST != errno )
		{
			printf( "Error in child\n" );
			print_error( f_code, "mkfifo" );
		}
	}

	fd = open( argv[1], O_RDONLY );

	do
	{
		read( fd, string, 127 );
		printf( "[child process] Read: %s\n", string );
	} while( strcmp( "quit", string ) != 0 );

	close( fd );

	return 0;
}
