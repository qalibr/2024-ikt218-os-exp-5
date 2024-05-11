#include "timer.h"

uint32_t tick = 0;

static void timerCallback(Registers_t r) {
    tick++;
    displayWrite("Tick: ");
    displayWriteDec(tick);
    displayWrite("\n");
}

void initTimer(uint32_t freq) {
    registerInterruptHandler(IRQ0, &timerCallback);

    uint32_t divisor = 1193180 / freq;

    outPortByte(0x43, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outPortByte(0x40, low);
    outPortByte(0x40, high);
}