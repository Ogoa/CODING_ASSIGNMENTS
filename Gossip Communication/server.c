#include "main.h"

/**
 * setup_server - Sets up the server that will accept requests from processes
 * and performs a service for them
 * @port: The port on which the server socket will be bound
 * This uniquely identifies the port on which the server is listening
 * to requests from
 *
 * Return: Nothing
 */
void setup_server(Process *process)
{
        Sock_addr serverAddr;
        Sock_addr connection_address;
        int option_value = 1;
        int status;
        int client_socket;
        char storage_buffer[BUFFER_SIZE];
        int address_len;
        int msg_len = 0;

        process->fd = create_socket();
        status = setsockopt(process->fd, SOL_SOCKET, SO_REUSEADDR,
                        &option_value, sizeof(option_value));
        /* Initialise 'serverAddr' with zeros */
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(process->port);
        /* Assign a name to the socket */
        if (bind(process->fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        {
                perror("Error while binding socket");
                fprintf(stderr, "Address: %s, Port: %d\n", process->ip, process->port);
                exit(EXIT_FAILURE);
        }

        if (listen(process->fd, 5) == -1) /* Maximum of 5 requests */
        {
                perror("Error listening on socket");
                exit(EXIT_FAILURE);
        }
        printf("Server listening on port %d\n", process->port);
        address_len = sizeof(connection_address);
        client_socket = accept(process->fd, (struct sockaddr *)&connection_address,
                        &address_len);
        if (client_socket == -1)
        {
                perror("Error accepting connection");
                exit(EXIT_FAILURE);
        }
        printf("Accepted connection from %s:%d\n", inet_ntoa(connection_address.sin_addr), ntohs(connection_address.sin_port));
        msg_len = read(client_socket, storage_buffer, BUFFER_SIZE);
        if (strcmp(storage_buffer, "NOT infected") == 0)
                send(client_socket, process->msg, strlen(process->msg), 0);
        else
                send(client_socket, NULL, 0, 0);
        close(process->fd);
        close(client_socket);
}
