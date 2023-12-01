#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "sockets.c"
#include "logical_clock.c"

typedef struct {
    int time_adjustment;
} BerkleyClock;

void init_berkley_clock(BerkleyClock* clock) {
    clock->time_adjustment = 0;
}

int calculate_time_adjustment(LogicalClock* local_clock, LogicalClock* received_clock) {
    return received_clock->value - local_clock->value;
}

void synchronize_time(LogicalClock* local_clock, BerkleyClock* berkley_clock, int time_adjustment) {
    local_clock->value += time_adjustment;
    berkley_clock->time_adjustment = time_adjustment;
}

