#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#include <spawn.h>
#include <signal.h>

char** environ;

void print_error( int e_num, char* e_msg )
{
	errno = e_num;
	perror( e_msg );
	exit( EXIT_FAILURE );
}

int main( int argc, char* argv[] )
{
	pid_t child_pid, own_pid, parent_pid;
	int f_code, child_status;
	// merg pe variantele implicite pentru semnale si fisiere
	posix_spawnattr_t* ptr_attr = NULL;
	posix_spawn_file_actions_t file_actions;
	posix_spawn_file_actions_t* ptr_file_actions = NULL;

	char next_key;
	int sig_no_value;

	own_pid = getpid( );
	parent_pid = getppid( );

	printf( "Parent process started with pid %jd/parent %jd\n", (intmax_t) own_pid, (intmax_t) parent_pid );

	printf( "Config child proc with no stdin...\n" );
	f_code = posix_spawn_file_actions_init( &file_actions );
	if( 0 != f_code )
	{
		print_error( f_code, "posix_spawn_file_actions_init" );
	}
	f_code = posix_spawn_file_actions_addclose( &file_actions, STDIN_FILENO );
	if( 0 != f_code )
	{
		print_error( f_code, "posix_spawn_file_actions_addclose" );
	}
	ptr_file_actions = &file_actions;

	printf( "Attempt to spawn new process for program \"%s\"...\n", argv[1] );
	f_code = posix_spawnp( &child_pid, argv[1], ptr_file_actions, ptr_attr, &argv[1], environ );
	if( 0 != f_code )
	{
			print_error( f_code, "posix_spawn" );
	}
	printf( "New process created successfully for \"%s\" - PID: %jd\n", argv[1], (intmax_t) child_pid );
	
	printf( "Cleanup - destroying file_actions... \n" );
	if( ptr_file_actions != NULL )
	{
		f_code = posix_spawn_file_actions_destroy( ptr_file_actions );
		if( 0 != f_code )
		{
			print_error( f_code, "posix_spawn_file_actions_destroy" );
		}
	}

	// read char and send signal to child
	while( EOF != ( next_key = fgetc( stdin ) ) )
	{
		sig_no_value = ( ( int ) next_key ) % 2;
		printf( "Read %c, sending SIG_USR%d to child\n", next_key, ( sig_no_value ? 1 : 2 ) );

		if( 1 == sig_no_value )
		{
			kill( child_pid, SIGUSR1 );
		}
		else
		{
			kill( child_pid, SIGUSR2 );
		}

		if( 'x' == next_key )
		{
			kill( child_pid, SIGQUIT );
			break;
		}

		sleep( 1 );
	}

	// wait for child to finish
	do
	{
		f_code = waitpid( child_pid, &child_status, WUNTRACED | WCONTINUED );
		if( -1 == f_code )
		{
			print_error( f_code, "waitpid" );
		}
		printf( "Child status: " );
		if( WIFEXITED( child_status ) )
		{
			printf( "finished, exit code: %d\n", WEXITSTATUS( child_status ) );
		}
		else
		{
			if( WIFSIGNALED( child_status ) )
			{
				printf( "killed by signal %d\n", WTERMSIG( child_status ) );
			}
			else
			{
				if( WIFSTOPPED( child_status ) )
				{
					printf( "stopped by signal %d\n", WSTOPSIG( child_status ) );
				}
				else
				{
					if( WIFCONTINUED( child_status ) )
					{
						printf( "running\n" );
					}
				}
			}
		}
	} while( 0 == WIFEXITED( child_status ) && 0 == WIFSIGNALED( child_status ) );

	return 0;
}
