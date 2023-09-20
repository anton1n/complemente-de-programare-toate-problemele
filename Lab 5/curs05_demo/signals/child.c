#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <errno.h>

#include <unistd.h>
#include <signal.h>

void print_error( int e_num, char* e_msg )
{
	errno = e_num;
	perror( e_msg );
	exit( EXIT_FAILURE );
}

void sig_usr1_handler( int signum )
{
	printf( "Parent read odd char code from keyboard\n" );
}

void sig_usr2_handler( int signum )
{
	printf( "Parent read even char code from keyboard\n" );
}

int main( int argc, char* argv [] )
{
	int iter;
	sig_t f_code;
	pid_t own_pid = getpid( );
	pid_t parent_pid = getppid( );
	printf( "Hello world from child process: pid %jd/parent pid %jd!\n", (intmax_t) own_pid, (intmax_t) parent_pid );

	printf( "Registering signal handlers...\n" );
	f_code = signal( SIGUSR1, sig_usr1_handler );
	if( SIG_ERR == f_code )
	{
		print_error( (int) ( (intmax_t) f_code ), "signal" );
	}
	f_code = signal( SIGUSR2, sig_usr2_handler );
	if( SIG_ERR == f_code )
	{
		print_error( (int) ( (intmax_t) f_code ), "signal" );
	}

	for( iter=0; iter<argc; ++iter )
	{
		printf( "arg no: %3d\tvalue: %s\n", iter, argv[iter] );
	}

	while( 1 ) // don't do this @ home :))))
	{
		sleep( 1 );
		pause( );
	}

	return 0;
}
