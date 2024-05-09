#ifndef ISR_H
#define ISR_H

#include "libc/stdint.h"
#include "system.h"
#include "display.h"
#include "libc/string.h"
#include "common.h"

#define INT_HANDLERS 256

extern void isrHandler(Registers_t r);
extern void irqHandler(Registers_t r);
typedef void (*isr_t)(Registers_t);
extern isr_t interruptHandlers[INT_HANDLERS];

void registerInterruptHandler(uint8_t n, isr_t handler);
void initInterruptHandlers();

#endif