#ifndef CLOCK_H
#define CLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define SERVER_PORT 5000
#define CLIENT_PORT 5001

// sockets.c function prototypes
int create_socket();
void bind_socket(int sockfd, int port);
void listen_for_connections(int sockfd);
int accept_connection(int sockfd);
void close_socket(int sockfd);
void send_message(int sockfd, const char* message);
void receive_message(int sockfd, char* buffer, size_t buffer_size);

// logical_clock.c function prototypes
typedef struct {
    int value;
} LogicalClock;

void init_logical_clock(LogicalClock* clock);
void increment_logical_clock(LogicalClock* clock);
void update_logical_clock(LogicalClock* clock, int received_value);
int get_logical_clock_value(LogicalClock* clock);

// berkley.c function prototypes
typedef struct {
    int time_adjustment;
} BerkleyClock;

void init_berkley_clock(BerkleyClock* clock);
int calculate_time_adjustment(LogicalClock* local_clock, LogicalClock* received_clock);
void synchronize_time(LogicalClock* local_clock, BerkleyClock* berkley_clock, int time_adjustment);

#endif /* CLOCK.H */
