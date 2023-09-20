#include "HeaderServer.h"

int main(int argc, char **argv)
{
    int server_fd, client_fd;
    struct sockaddr_in *server_address = 0;

    server_fd = configureSocket();
    server_address = getServer(argc,argv);
    client_fd = connection(server_fd, *server_address);

    communication(client_fd);

    close(server_fd);

    return 0;
}