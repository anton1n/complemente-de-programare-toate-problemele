#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_PORT	4092

int main( void )
{
	int server_fd, client_fd, input_message_size;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int err_setopt = 0;
	int option_value = 1;
	int address_length = ( int ) sizeof( server_address );

	char input_buffer[1024] = { 0 };

	int should_run = 1;

	// server_fd = socket( AF_INET, SOCK_STREAM, 0 );
	server_fd = socket( PF_INET, SOCK_STREAM, 0 );

	if( -1 == server_fd )
	{

		fprintf( stderr, "Nu pot crea socket-ul\n" );
		exit( EXIT_FAILURE );
	}

	err_setopt = setsockopt( server_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value) );

	if( 0 != err_setopt )
	{
		fprintf( stderr, "Nu pot configura socket-ul: SO_REUSEADDR\n" );
		perror( "setsockopt call failed" );
		exit( EXIT_FAILURE );
	}

	err_setopt = setsockopt( server_fd, SOL_SOCKET, SO_REUSEPORT, &option_value, sizeof(option_value) );

	if( 0 != err_setopt )
	{
		fprintf( stderr, "Nu pot configura socket-ul: SO_REUSEADDR\n" );
		perror( "setsockopt call failed" );
		exit( EXIT_FAILURE );
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
    	server_address.sin_port = htons( SERVER_PORT );

	if( 0 > bind( server_fd, (struct sockaddr *) &server_address, sizeof( server_address ) ) )
	{
		fprintf( stderr, "Nu pot deschide socket-ul pentru a primi mesaje\n" );
		exit( EXIT_FAILURE );
	}

	if( 0 > listen( server_fd, 1 ) )
	{
		fprintf( stderr, "Nu pot accepta conexiuni\n" );
		exit( EXIT_FAILURE );
	}

	client_fd = accept( server_fd, (struct sockaddr *) &client_address, ( socklen_t *) &address_length );

	if( 0 > client_fd )
	{
		fprintf( stderr, "Eroare la conectarea clientului\n" );
		exit( EXIT_FAILURE );
	}

	while( 1 == should_run )
	{
		memset( input_buffer, 0x00, 1024 * sizeof(char) );

		input_message_size = read( client_fd, input_buffer, 1024 );
		if( NULL != strstr( input_buffer, "exit" ) )
		{
			printf( "Am primit exit... inchid conexiunea\n" );
			should_run = 0;
			close( client_fd );
			continue;
		}

		printf( "Am primit %d octeti. Mesajul este: %s\n", input_message_size, input_buffer );		
		send( client_fd, input_buffer, strlen( input_buffer )+1, 0 ); //
	}

	close( server_fd );

	return 0;
}
