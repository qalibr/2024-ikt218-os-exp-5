#ifndef ISR_H
#define ISR_H

#include "libc/stdint.h"
#include "system.h"
#include "display.h"
#include "libc/string.h"
#include "common.h"

#define INT_HANDLERS 256

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

extern void IsrHandler(Registers_t r);
extern void IrqHandler(Registers_t r);
typedef void (*isr_t)(Registers_t);
extern isr_t interruptHandlers[INT_HANDLERS];

void RegisterInterruptHandler(uint8_t n, isr_t handler);
void InitInterruptHandlers();

#endif