#include "main.h"

/**
 * main - Execute the server functionality
 * @argc: Number of arguments passed into the program
 * @argv: An array of arguments passed into the program in the terminal
 *
 * Return: Always 0 (Successful exit)
 */
int main(int argc, char **argv)
{
	int socket_fd;
	int newsock_fd;
	Sock server_addr;
	Sock client_addr;
	socklen_t client_len;
	char buffer[BUFFER_SIZE];
	int bytes_read = 0, bytes_written = 0, port;

	if (argc != 2)
		print_error("Usage: program port_no");

	/* Open the socket */
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		print_error("Error opening socket");
	bzero((char *)&server_addr, sizeof(server_addr));
	port = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	/* Bind the socket to an address in the address space */
	if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		print_error("Binding failed");
	/* Start listening */
	listen(socket_fd, 5);
        client_len = sizeof(client_addr);
        newsock_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
        if (newsock_fd < 0)
                print_error("Error on accept");
        while (1)
        {
                bzero(buffer, BUFFER_SIZE);
                bytes_read = read(newsock_fd, buffer, BUFFER_SIZE);
                if (bytes_read < 0)
                        print_error("Error on reading");
                printf("Client message: %s\n", buffer);
                bzero(buffer, BUFFER_SIZE);
                fgets(buffer, BUFFER_SIZE, stdin);

                if (write(newsock_fd, buffer, bytes_read) < 0)
                        print_error("Error on writing");

                /* Condition to exit the loop */
                if (strncmp("Bye", buffer, 3) == 0)
                        break;
        }
        close(newsock_fd);
        close(socket_fd);
	return (0);
}
