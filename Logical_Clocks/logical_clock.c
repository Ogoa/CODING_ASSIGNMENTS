#include "clock.h"

void init_logical_clock(LogicalClock* clock) {
    clock->value = 0;
}

void increment_logical_clock(LogicalClock* clock) {
    clock->value++;
}

void update_logical_clock(LogicalClock* clock, int received_value) {
    clock->value = (received_value > clock->value) ? received_value + 1 : clock->value + 1;
}

int get_logical_clock_value(LogicalClock* clock) {
    return clock->value;
}

