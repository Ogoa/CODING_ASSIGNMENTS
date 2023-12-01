#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "sockets.c"
#include "logical_clock.c"
#include "berkley.c"

LogicalClock process_clock;
BerkleyClock berkley_clock;

void* process_function(void* arg) {
    int client_sock = *(int*)arg;

    srand(time(NULL) + getpid());
    int interval = rand() % 5 + 1;

    while (1) {
        char message[50];
        sprintf(message, "%d", get_logical_clock_value(&process_clock));
        send_message(client_sock, message);

        increment_logical_clock(&process_clock);
        sleep(interval);
    }
}

int main() {
    init_logical_clock(&process_clock);
    init_berkley_clock(&berkley_clock);

    int server_sock = create_socket();
    bind_socket(server_sock, SERVER_PORT);
    listen_for_connections(server_sock);

    printf("Waiting for connections...\n");
    int client_sock = accept_connection(server_sock);
    printf("Connection established.\n");

    pthread_t thread_P;
    pthread_create(&thread_P, NULL, process_function, (void*)&client_sock);

    char buffer[50];
    while (1) {
        receive_message(client_sock, buffer, sizeof(buffer));
        int received_clock_value = atoi(buffer);
        
        int time_adjustment = calculate_time_adjustment(&process_clock, &berkley_clock);
        synchronize_time(&process_clock, &berkley_clock, time_adjustment);

        printf("Received: %s | Adjusted Time: %d\n", buffer, get_logical_clock_value(&process_clock));
    }

    close_sockets(server_sock, client_sock);
    return 0;
}

