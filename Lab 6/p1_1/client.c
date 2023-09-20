#include "HeaderClient.h"

int main(int argc, char **argv)
{
	int socket_fd;
	struct sockaddr_in * server_address = 0;

	socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if( -1 == socket_fd )
	{
		fprintf( stderr, "Nu pot crea socket-ul\n" );
		exit( EXIT_FAILURE );
	}

	server_address = getServer(argc, argv);

	connectToServer(socket_fd, *server_address);

	communication(socket_fd);

	return 0;
}
