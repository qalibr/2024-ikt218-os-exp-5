/* Source: 
- UiA, Per-Arne Lecture/Assignment Assets
- https://web.archive.org/web/20190216040308/http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html */

#ifndef ISR_H
#define ISR_H

#include "libc/stdint.h"
#include "system.h"
#include "io/display.h"
#include "libc/string.h"
#include "io/port.h"
#include "descriptors/idt.h"

#define IRQ_COUNT 16

typedef void (*isr_t)(Registers_t*, void*); // Function pointer with arguments: registers, and context (data).
struct interruptHandler_t {
    int num;
    isr_t handler;
    void *data;
};

extern void IsrHandler(Registers_t r);
static struct interruptHandler_t interruptHandlers[IDT_ENTRIES];
void RegisterInterruptHandler(uint8_t n, isr_t handler, void *context);
void InitInterruptHandlers();


extern void IrqHandler(Registers_t r);
static struct interruptHandler_t irqHandlers[IRQ_COUNT];
void RegisterIrqHandler(uint8_t irq, isr_t handler, void *context);
void InitIrqHandlers();

#define ISR0 0
#define ISR1 1
#define ISR2 2
#define ISR3 3
#define ISR4 4
#define ISR5 5
#define ISR6 6
#define ISR7 7
#define ISR8 8
#define ISR9 9
#define ISR10 10
#define ISR11 11
#define ISR12 12
#define ISR13 13
#define ISR14 14
#define ISR15 15
#define ISR16 16
#define ISR17 17
#define ISR18 18
#define ISR19 19
#define ISR20 20
#define ISR21 21
#define ISR22 22
#define ISR23 23
#define ISR24 24
#define ISR25 25
#define ISR26 26
#define ISR27 27
#define ISR28 28
#define ISR29 29
#define ISR30 30
#define ISR31 31
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

#endif