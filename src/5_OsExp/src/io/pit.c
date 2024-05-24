/* Source: UiA, Per-Arne Lecture/Assignment Assets */

#include "io/pit.h"

uint32_t tick = 0;

// PIT handler mapped to IRQ0 (system timer). 
// When the interrupt request is answered the handler runs and increments the tick variable.
void PitIrqHandler(Registers_t *r, void *context) {
    tick++;
}

void InitPit() {
    RegisterIrqHandler(IRQ0, &PitIrqHandler, NULL); // Register PIT handler (called from interrupt.asm)

    OutPortByte(PIT_CMD_PORT, 0x36); // Configure the PIT

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

    // Busy wait loop CPU actively increments ticks
    while (elapsedTicks < ticksToWait) {
        while (tick == initialTick + elapsedTicks) { };
        elapsedTicks++;
    }
}

void SleepInterrupt(uint32_t ms) {
    uint32_t initialTick = tick;
    uint32_t ticksToWait = ms * TICKS_PER_MS;
    uint32_t endTicks = initialTick + ticksToWait;

    // Sleep interrupt halts the CPU until its time to wake up
    while (initialTick < endTicks) {
        asm volatile("sti"); // Enable interrupts
        asm volatile("hlt"); // Halt CPU

        initialTick = tick;
    }
    
}