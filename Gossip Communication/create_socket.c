#include "main.h"

/**
 * create_socket - Creates a socket
 *
 * Return: The file descriptor for the socket being opened
 */
int create_socket(void)
{
        int socket_fd;

        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (!socket_fd)
        {
                perror("Error creating the socket");
                exit(EXIT_FAILURE);
        }
        return (socket_fd);
}
