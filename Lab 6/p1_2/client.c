#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int socket_fd;
    struct sockaddr_in server_address;
    char input_message[1024] = {0}, transmission_buffer[1024] = {0};
    int should_run = 1;
    socklen_t server_address_size = sizeof(server_address);
    int message_size;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4092);
	inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if(argc == 3)
    {
        server_address.sin_port = htons( atoi(argv[1]) );
        if( 0 >= inet_pton( AF_INET, argv[2], &server_address.sin_addr ) )
        {
            fprintf( stderr, "Adresa este invalida\n" );
            exit( EXIT_FAILURE );
        }
    }

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( -1 == socket_fd )
	{
		fprintf( stderr, "Nu pot crea socket-ul\n" );
		exit( EXIT_FAILURE );
	}

    while( 1 == should_run )
	{
        memset(transmission_buffer,0,sizeof(transmission_buffer));
		if( NULL != fgets( input_message, 1024, stdin ) ) 
		{

			input_message[strlen(input_message)-1] = '\0'; 
            sendto(socket_fd, input_message, strlen(input_message), 0, (struct sockaddr*)&server_address, sizeof(server_address));
			if( 0 == strcmp( "exit", input_message ) )
			{
				should_run = 0;
				continue;
			}
            message_size = recvfrom(socket_fd, transmission_buffer, sizeof(transmission_buffer), 0,(struct sockaddr*)&server_address, &server_address_size);
			printf( "Receptionat de la server: %s [dimensiune: %d]\n", transmission_buffer, (int)message_size );
		}
	}

    printf( "Inchid conexiunea\n" );
	close( socket_fd );

    return 0;
}
