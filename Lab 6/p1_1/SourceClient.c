#include "HeaderClient.h"

struct sockaddr_in *getServer(int argc, char **argv)
{
	struct sockaddr_in *server_address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	

	server_address->sin_family = AF_INET;
	server_address->sin_port = htons(4092);
	inet_pton(AF_INET, "127.0.0.1", &server_address->sin_addr);

	if(argc == 3)
	{
		server_address->sin_port = htons(atoi(argv[1]));
		if( 0 >= inet_pton( AF_INET, argv[2], &server_address->sin_addr ) )
		{
			fprintf( stderr, "Adresa este invalida\n" );
			exit( EXIT_FAILURE );
		}
	}

	return server_address;
}

void connectToServer(int socket_fd, struct sockaddr_in server_address)
{
	if( 0 > connect( socket_fd, (struct sockaddr *) &server_address, sizeof( server_address ) ) )
	{
		fprintf( stderr, "Nu pot realiza conexiunea cu server-ul\n" );
		exit( EXIT_FAILURE );
	}

	printf( "M-am conectat la server\n" );
}

void communication(int socket_fd)
{
	int should_run = 1;
	char line[1024] = { 0 }, transmission_buffer[1024] = { 0 };
	int input_message_size;

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
}