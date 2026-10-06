#include "timer.h"
#include "io.h"

static volatile uint32_t ticks = 0;

void timer_handler(void) {
    ticks++;
    outb(0x20, 0x20);
}

uint32_t timer_get_ticks(void) {
    return ticks;
}
