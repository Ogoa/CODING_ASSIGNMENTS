#include "main.h"

/**
 * main - Execute the server functionality
 * @argc: Number of arguments passed into the program
 * @argv: An array of arguments passed into the program in the terminal
 *
 * Return: Always 0 (Successful exit)
 */
int main(void)
{
	int socket_fd;
	Sock server_addr;
	Sock client_addr;
	int port, n;
	socklen_t client_len;

	if (argc != 2)
		print_error("Usage: program port_no");

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		print_error("Error opening socket");
	bzero((char *)&server_addr, sizeof(server_addr));
	port = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		print_error("Binding failed");
	return (0);
}
