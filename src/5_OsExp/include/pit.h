#ifndef PIT_H
#define PIT_H

#include "libc/stdint.h"
#include "common.h"
#include "system.h"
#include "io/display.h"
#include "interrupt/isr.h"
#include "libc/stdio.h"

// PIT (Programmable Interval Timer)
#define PIT_CMD_PORT 0x43
#define PIT_CHANNEL0_PORT 0x40
#define PIT_CHANNEL1_PORT 0x41
#define PIT_CHANNEL2_PORT 0x42
#define PC_SPEAKER_PORT 0x61
#define PIT_DEFAULT_DIVISOR 0x4E20 // ~18.2 Hz (1193180 / 20000)

// IRQ0
#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x20
#define PIC_EOI 0x20

// Custom constants for sleep functions
#define PIT_BASE_FREQUENCY 1193180
#define TARGET_FREQUENCY 1000
#define DIVIDER (PIT_BASE_FREQUENCY / TARGET_FREQUENCY)
#define TICKS_PER_MS (TARGET_FREQUENCY / TARGET_FREQUENCY)

void InitPit();

void PitIrqHandler(Registers_t *r, void *context);

void SleepInterrupt(uint32_t ms);

void SleepBusy(uint32_t ms);

#endif