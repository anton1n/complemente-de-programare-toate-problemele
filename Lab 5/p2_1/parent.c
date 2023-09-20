#include <stdio.h>
#include <spawn.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

//a se rula cu sudo datorita permisiunilor

char **environ;

void print_error( int e_num, char* e_msg )
{
	errno = e_num;
	perror( e_msg );
	exit( EXIT_FAILURE );
}

int main()
{
    int verif, child_status;
    posix_spawnattr_t* ptr_attr = NULL;
	posix_spawn_file_actions_t* ptr_file_actions = NULL;
    pid_t child_pid;

    char* argv[] = { "child1", "child2", NULL };
    
    verif = posix_spawn(&child_pid, argv[0], ptr_file_actions, ptr_attr, &argv[0], environ);
    if(0 != verif)
    {
        print_error(verif, "posix_spawn");
    }
    
    do
	{
		verif = waitpid( child_pid, &child_status, WUNTRACED | WCONTINUED );
		if( -1 == verif )
		{
			print_error( verif, "waitpid" );
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

    verif = posix_spawn(&child_pid, argv[1], ptr_file_actions, ptr_attr, &argv[1], environ);
    if(0 != verif)
    {
        print_error(verif, "posix_spawn");
    }
    
    do
	{
		verif = waitpid( child_pid, &child_status, WUNTRACED | WCONTINUED );
		if( -1 == verif )
		{
			print_error( verif, "waitpid" );
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


}