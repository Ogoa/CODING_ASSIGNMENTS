#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 256

typedef struct sockaddr_in Sock;

void print_error(const char *err);

#endif /* ifndef MAIN_H */
