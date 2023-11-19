#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_NODES 5
#define IP_ADDRESS "127.0.0.1"
#define BASE_PORT 9000
#define BUFFER_SIZE 120

typedef struct sockaddr_in Sock_addr;

/**
 * struct node - A structure representing a process running in a machine
 * @fd: The file descriptor returned from opening a socket
 * @port: The port the process is using
 * @id: The process ID
 * @ip: The ip address of the socket
 * @connect: A list of other processes the process is directly connected to
 *
 * Description: This structure is a process running in a node within
 * a distributed system
 */
typedef struct node
{
        int fd;
        int port;
        int id;
        char *ip;
        char *msg;
        struct node **connected;
        int visited[5];
} Process;

/**
 * struct message - A structure representing a message that will be sent
 * between two processes
 * @sender_id: Process id of the infected node that is gossiping
 * @text: The actual payload of the message
 */
typedef struct message
{
        int sender_id;
        char *text;
} Message;

int create_socket(void);
Process **init_nodes(void);
void setup_server(Process *process);
void setup_client(Process *process);

#endif /* ifndef MAIN_H */
