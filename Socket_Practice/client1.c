#include "main.h"

/**
 * main - Execute the functionality of a client computer
 * @argc: The number of arguments passed into the program
 * @argv: An array of arguments passed into the program at the terminal
 *
 * Return: Always 0 (Successful exit)
 * Description: This program has to have three arguments passed into it
 * Usage: filename server_ip_address portno
 */
int main(int argc, char **argv)
{
	int socket_fd;
	int port, bytes_read = 0, n = 0;
	Sock server_addr;
	char buffer[BUFFER_SIZE];
	struct hostent *server;

	if (argc != 3)
		print_error("Usage: filename server_ip_address portno");
	port = atoi(argv[2]);
	/* Open the socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		print_error("Error opening socket");
	/* Get the server ip_address provided by the user */
	server = gethostbyname(argv[1]);
	if (server == NULL)
		print_error("Error, no such host");
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr,
			server->h_length);
	server_addr.sin_port = htons(port);
	if (connect(socket_fd, (struct sockaddr *) &server_addr,
				sizeof(server_addr)) < 0)
		print_error("Connection failed");
	while (1)
	{
		bzero(buffer, BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, stdin);
		n = write(socket_fd, buffer, strlen(buffer));
		if (n < 0)
			print_error("Error on writing");
		bzero(buffer, BUFFER_SIZE);
		bytes_read = read(socket_fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			print_error("Error on reading");
		printf("Server message: %s\n", buffer);
		/* Termination condition */
		if (strncmp("Bye", buffer, 3) == 0)
			break;
	}
	close(socket_fd);
	return (0);
}
