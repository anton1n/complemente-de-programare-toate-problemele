#ifndef HEADERCLIENT_H_
#define HEADERCLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in *getServer(int argc, char **argv);
void connectToServer(int socket_fd, struct sockaddr_in server_address);
void communication(int socket_fd);

#endif
