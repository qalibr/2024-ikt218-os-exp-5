#ifndef IDT_H
#define IDT_H

#include "libc/stdint.h"
#include "common.h"
#include "system.h"
#include "io/display.h"
#include "libc/string.h"

#define IDT_ENTRIES 256

// Define a single entry of the IDT. Descriptors for segments.
struct idtEntry_t {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t baseHigh;
} __attribute__((packed));

// Size and address of the IDT
struct idtPtr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void InstallIdt();

// Configuration for a single entry.
void IdtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

static struct idtEntry_t idt[IDT_ENTRIES];     // Array of IDT entries
static struct idtPtr_t idtPtr;                 // Pointer to IDT

extern void Isr0();
extern void Isr1();
extern void Isr2();
extern void Isr3();
extern void Isr4();
extern void Isr5();
extern void Isr6();
extern void Isr7();
extern void Isr8();
extern void Isr9();
extern void Isr10();
extern void Isr11();
extern void Isr12();
extern void Isr13();
extern void Isr14();
extern void Isr15();
extern void Isr16();
extern void Isr17();
extern void Isr18();
extern void Isr19();
extern void Isr20();
extern void Isr21();
extern void Isr22();
extern void Isr23();
extern void Isr24();
extern void Isr25();
extern void Isr26();
extern void Isr27();
extern void Isr28();
extern void Isr29();
extern void Isr30();
extern void Isr31();
extern void Irq0 ();
extern void Irq1 ();
extern void Irq2 ();
extern void Irq3 ();
extern void Irq4 ();
extern void Irq5 ();
extern void Irq6 ();
extern void Irq7 ();
extern void Irq8 ();
extern void Irq9 ();
extern void Irq10();
extern void Irq11();
extern void Irq12();
extern void Irq13();
extern void Irq14();
extern void Irq15();

#endif