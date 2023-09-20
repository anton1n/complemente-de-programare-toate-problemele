#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_PORT 4092

int main( void )
{
	char line[1024] = { 0 }, transmission_buffer[1024] = { 0 };
	int input_message_size;

	int socket_fd;
	struct sockaddr_in server_address;
	int err_connect;

	int should_run = 1;

	socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if( -1 == socket_fd )
	{
		fprintf( stderr, "Nu pot crea socket-ul\n" );
		exit( EXIT_FAILURE );
	}

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons( SERVER_PORT );
	if( 0 >= inet_pton( AF_INET, "127.0.0.1", &server_address.sin_addr ) )
	{
		fprintf( stderr, "Adresa este invalida\n" );
		exit( EXIT_FAILURE );
	}

	err_connect = connect( socket_fd, (struct sockaddr *) &server_address, sizeof( server_address ) );
	if( 0 > err_connect )
	{
		fprintf( stderr, "Nu pot realiza conexiunea cu server-ul\n" );
		exit( EXIT_FAILURE );
	}

	printf( "M-am conectat la server\n" );

	while( 1 == should_run )
	{
		if( NULL != fgets( line, 1024, stdin ) ) 
		{
			input_message_size = strlen( line );
			line[input_message_size-1] = '\0'; 
			send( socket_fd, line, input_message_size-1, 0 );
			if( 0 == strcmp( "exit", line ) )
			{
				should_run = 0;
				continue;
			}
			input_message_size = read( socket_fd, transmission_buffer, 1024 );
			printf( "Receptionat de la server: %s [dimensiune: %d]\n", transmission_buffer, input_message_size );
		}
	}

	printf( "Inchid conexiunea\n" );
	close( socket_fd );

	return 0;
}
