#include "pit.h"

uint32_t tick = 0;

void PitIrqHandler(Registers_t *r, void *context) {
    tick++;
}

void InitPit() {
    RegisterIrqHandler(IRQ0, &PitIrqHandler, NULL);

    OutPortByte(PIT_CMD_PORT, 0x36);

    uint32_t divisor = PIT_BASE_FREQUENCY / TARGET_FREQUENCY;

    // Split up divisor
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    // Send divisor
    OutPortByte(PIT_CHANNEL0_PORT, low);
    OutPortByte(PIT_CHANNEL0_PORT, high);
}

void SleepBusy(uint32_t ms) {
    uint32_t initialTick = tick;
    uint32_t ticksToWait = ms * TICKS_PER_MS;
    uint32_t elapsedTicks = 0;

    while (elapsedTicks < ticksToWait) {
        while (tick == initialTick + elapsedTicks) { };
        elapsedTicks++;
    }
}

void SleepInterrupt(uint32_t ms) {
    uint32_t initialTick = tick;
    uint32_t ticksToWait = ms * TICKS_PER_MS;
    uint32_t endTicks = initialTick + ticksToWait;

    while (initialTick < endTicks) {
        asm volatile("sti"); // Enable interrupts
        asm volatile("hlt"); // Halt CPU

        initialTick = tick;
    }
}