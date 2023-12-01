#include "clock.h"

int create_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void bind_socket(int sockfd, int port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
}

void listen_for_connections(int sockfd) {
    if (listen(sockfd, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }
}

int accept_connection(int sockfd) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_sock = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_sock == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    return client_sock;
}

void close_socket(int sockfd) {
    close(sockfd);
}

void send_message(int sockfd, const char* message) {
    send(sockfd, message, strlen(message), 0);
}

void receive_message(int sockfd, char* buffer, size_t buffer_size) {
    ssize_t bytes_received = recv(sockfd, buffer, buffer_size - 1, 0);
    if (bytes_received == -1) {
        perror("Error receiving message");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_received] = '\0';  // Null-terminate the received message
}

