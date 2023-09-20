#ifndef HEADERSERVER_H_
#define HEADERSERVER_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

struct sockaddr_in *getServer(int argc, char **argv);
int configureSocket();
int connection(int server_fd, struct sockaddr_in server_address);
void communication(int client_fd);



#endif