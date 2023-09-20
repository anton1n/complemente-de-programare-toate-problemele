#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
    int socket_fd;
    struct sockaddr_in server_address;
	struct sockaddr_in client_address;
    int should_run = 1;
    char message[1024];
    socklen_t address_length =sizeof( client_address );
    int message_size;

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( -1 == socket_fd )
	{

		fprintf( stderr, "Nu pot crea socket-ul\n" );
		exit( EXIT_FAILURE );
	}

    server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( 4092 );

    if(argc == 2)
    {
        server_address.sin_port = htons( atoi(argv[1]) );
    }

    if( 0 > bind( socket_fd, (struct sockaddr *) &server_address, sizeof( server_address ) ) )
	{
		fprintf( stderr, "Nu pot deschide socket-ul pentru a primi mesaje\n" );
		exit( EXIT_FAILURE );
	}

    while( 1 == should_run )
	{
		memset( message, 0x00, 1024 * sizeof(char) );

		message_size = recvfrom(socket_fd, message, sizeof(message), 0, (struct sockaddr*)&client_address, &address_length);
		if( NULL != strstr( message, "exit" ) )
		{
			printf( "Am primit exit... inchid conexiunea\n" );
			should_run = 0;
			continue;
		}

		printf( "Am primit %d octeti. Mesajul este: %s\n", message_size, message );		
        sendto(socket_fd, message, strlen(message), 0,(struct sockaddr*)&client_address, address_length);
    }


    close(socket_fd);
}