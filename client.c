#include "main.h"

/**
 * main - Implements the client process code
 *
 * Return: Always 0 (Successful exit)
 */
int main(void)
{
	int socket_fd;
	char *message = "This is a message from the CLIENT!\n";
	char receive_buffer[100]; /* Buffer to receive messages */
	int status = 0;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (!socket_fd)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htcons(CONNECTION_PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_zer[8]='\0';
	/* Connect to the server */
	status = connect(socket_fd, (struct sockaddr*)&server_address,
			sizeof(server_address));
	write(socket_fd, message, strlen(message));
	read(socket_fd, receive_buffer, 100);
	printf("Message from server: %s\n", receive_buffer);
	close(socket_fd);
	return (0);
}
