#include "timer.h"

uint32_t tick = 0;

static void TimerCallback(Registers_t r) {
    tick++;
    DisplayWrite("Tick: ");
    DisplayWriteDec(tick);
    DisplayWrite("\n");
}

void InitTimer(uint32_t freq) {
    RegisterInterruptHandler(IRQ0, &TimerCallback);

    uint32_t divisor = 1193180 / freq;

    OutPortByte(0x43, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    OutPortByte(0x40, low);
    OutPortByte(0x40, high);
}