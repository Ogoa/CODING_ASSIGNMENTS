#include "main.h"

/**
 * setup_client - Set up a client that will request the server for resources
 * @ip: The IP address of the client process
 * @port: The port number the client is sending its requests through
 *
 * Return: Nothing
 */
void setup_client(Process *process)
{
        Sock_addr clientAddr;
        char buffer[120]; /* Buffer to receive messages */
        char *msg = "I am infected";
        char *msg2 = "NOT infected";

        process->fd = create_socket();
        /* Initialise the memory area of 'clientAddr' with zeros */
        memset(&clientAddr, 0, sizeof(clientAddr));
        clientAddr.sin_family = AF_INET;
        clientAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
        clientAddr.sin_port = htons(process->fd);

        if (!connect(process->fd, (struct sockaddr *)&clientAddr, sizeof(clientAddr)))
        {
                perror("Error connecting to server");
                exit(EXIT_FAILURE);
        }
        if (process->msg)
                write(process->fd, msg, strlen(msg));
        else
                write(process->fd, msg2, strlen(msg2));
        read(process->fd, buffer, 100);
        close(process->fd);
}
