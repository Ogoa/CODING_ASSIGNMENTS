#include "main.h"

/**
 * main - Implements the server process code
 *
 * Return: Always 0 (Successful exit)
 */
int main(void)
{
	int socket_fd;
	int status;
	char *message = "This is a message from the SERVER!\n";
	int option_value = 1;
	int address_len;
	char storage_buffer[80];
	int client_socket;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (!socket_fd)
	{
		perror("Server socket creation failed");
		exit(EXIT_FAILURE);
	}
	status = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR,
			&option_value, sizeof(option_value));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htcons(CONNECTION_PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_zero[8]='\0';
	status = bind(socket_fd, (struct sockaddr*)&server_address,
			sizeof(struct sockaddr));
	status = listen(socket_fd, 4); /* Maximum of 4 requests */
	address_len = sizeof(connection_address);
	client_socket = (socket_fd, (struct sockaddr*)&connection_address,
			&address_len);
	read(client_socket, storage_buffer, 80);
	storage_buffer[bytes_read] = '\0;
	printf("Message from client: %s \n", storage_buffer);
	/* Send data to the client */
	send(client_socket, message, strlen(message), 0);
	close(socket_fd); /* Close the socket file descriptor */
	close(client_socket);
	return (0);
}
