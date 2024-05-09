#ifndef IDT_H
#define IDT_H

#include "libc/stdint.h"
#include "system.h"
#include "display.h"
#include "libc/string.h"

#define IDT_ENTRIES 256

struct _idtEntry_t {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t always0;
    uint16_t baseHigh;
    uint8_t flags;
} __attribute__((packed));

struct _idtPtr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void installIdt();
void idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

static struct _idtEntry_t idt[IDT_ENTRIES];
static struct _idtPtr_t idtPtr;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif