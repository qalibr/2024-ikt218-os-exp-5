#include "idt.h"

#define IDT_ENTRIES 256

extern void idtFlush(uint32_t idtPtr);

void idtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].baseLow = base & 0xFFFF;
    idt[num].selector = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags /*| 0x60*/;
    idt[num].baseHigh = (base >> 16) & 0xFFFF;
}

void installIdt() {
    idtPtr.limit = sizeof(struct _idtEntry_t) * IDT_ENTRIES - 1;
    idtPtr.base = (uint32_t)&idt;

    memSet((uint8_t *)&idt, 0, sizeof(struct _idtEntry_t) * IDT_ENTRIES);

    // Remapping IRQ table
    outPortByte(0x20, 0x11);
    outPortByte(0xA0, 0x11);
    outPortByte(0x21, 0x20);
    outPortByte(0xA1, 0x28);
    outPortByte(0x21, 0x04);
    outPortByte(0xA1, 0x02);
    outPortByte(0x21, 0x01);
    outPortByte(0xA1, 0x01);
    outPortByte(0x21, 0x0);
    outPortByte(0xA1, 0x0);

    idtSetGate(0, (uint32_t)isr0, 0x08, 0x8E);
    idtSetGate(1, (uint32_t)isr1, 0x08, 0x8E);
    idtSetGate(2, (uint32_t)isr2, 0x08, 0x8E);
    idtSetGate(3, (uint32_t)isr3, 0x08, 0x8E);
    idtSetGate(4, (uint32_t)isr4, 0x08, 0x8E);
    idtSetGate(5, (uint32_t)isr5, 0x08, 0x8E);
    idtSetGate(6, (uint32_t)isr6, 0x08, 0x8E);
    idtSetGate(7, (uint32_t)isr7, 0x08, 0x8E);
    idtSetGate(8, (uint32_t)isr8, 0x08, 0x8E);
    idtSetGate(9, (uint32_t)isr9, 0x08, 0x8E);
    idtSetGate(10, (uint32_t)isr10, 0x08, 0x8E);
    idtSetGate(11, (uint32_t)isr11, 0x08, 0x8E);
    idtSetGate(12, (uint32_t)isr12, 0x08, 0x8E);
    idtSetGate(13, (uint32_t)isr13, 0x08, 0x8E);
    idtSetGate(14, (uint32_t)isr14, 0x08, 0x8E);
    idtSetGate(15, (uint32_t)isr15, 0x08, 0x8E);
    idtSetGate(16, (uint32_t)isr16, 0x08, 0x8E);
    idtSetGate(17, (uint32_t)isr17, 0x08, 0x8E);
    idtSetGate(18, (uint32_t)isr18, 0x08, 0x8E);
    idtSetGate(19, (uint32_t)isr19, 0x08, 0x8E);
    idtSetGate(20, (uint32_t)isr20, 0x08, 0x8E);
    idtSetGate(21, (uint32_t)isr21, 0x08, 0x8E);
    idtSetGate(22, (uint32_t)isr22, 0x08, 0x8E);
    idtSetGate(23, (uint32_t)isr23, 0x08, 0x8E);
    idtSetGate(24, (uint32_t)isr24, 0x08, 0x8E);
    idtSetGate(25, (uint32_t)isr25, 0x08, 0x8E);
    idtSetGate(26, (uint32_t)isr26, 0x08, 0x8E);
    idtSetGate(27, (uint32_t)isr27, 0x08, 0x8E);
    idtSetGate(28, (uint32_t)isr28, 0x08, 0x8E);
    idtSetGate(29, (uint32_t)isr29, 0x08, 0x8E);
    idtSetGate(30, (uint32_t)isr30, 0x08, 0x8E);
    idtSetGate(31, (uint32_t)isr31, 0x08, 0x8E);
    idtSetGate(32, (uint32_t)irq0, 0x08, 0x8E);
    idtSetGate(33, (uint32_t)irq1, 0x08, 0x8E);
    idtSetGate(34, (uint32_t)irq2, 0x08, 0x8E);
    idtSetGate(35, (uint32_t)irq3, 0x08, 0x8E);
    idtSetGate(36, (uint32_t)irq4, 0x08, 0x8E);
    idtSetGate(37, (uint32_t)irq5, 0x08, 0x8E);
    idtSetGate(38, (uint32_t)irq6, 0x08, 0x8E);
    idtSetGate(39, (uint32_t)irq7, 0x08, 0x8E);
    idtSetGate(40, (uint32_t)irq8, 0x08, 0x8E);
    idtSetGate(41, (uint32_t)irq9, 0x08, 0x8E);
    idtSetGate(42, (uint32_t)irq10, 0x08, 0x8E);
    idtSetGate(43, (uint32_t)irq11, 0x08, 0x8E);
    idtSetGate(44, (uint32_t)irq12, 0x08, 0x8E);
    idtSetGate(45, (uint32_t)irq13, 0x08, 0x8E);
    idtSetGate(46, (uint32_t)irq14, 0x08, 0x8E);
    idtSetGate(47, (uint32_t)irq15, 0x08, 0x8E);
    
    idtFlush((uint32_t)&idtPtr);
}