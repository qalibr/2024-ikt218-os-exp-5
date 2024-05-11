#include "descriptors/idt.h"

#define IDT_ENTRIES 256

extern void IdtFlush(uint32_t idtPtr);

void IdtSetGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].baseLow = base & 0xFFFF;
    idt[num].selector = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags /*| 0x60*/;
    idt[num].baseHigh = (base >> 16) & 0xFFFF;
}

void InstallIdt() {
    idtPtr.limit = sizeof(struct idtEntry_t) * IDT_ENTRIES - 1;
    idtPtr.base = (uint32_t)&idt;

    MemSet((uint8_t *)&idt, 0, sizeof(struct idtEntry_t) * IDT_ENTRIES);

    // Remapping IRQ table
    OutPortByte(0x20, 0x11);
    OutPortByte(0xA0, 0x11);
    OutPortByte(0x21, 0x20);
    OutPortByte(0xA1, 0x28);
    OutPortByte(0x21, 0x04);
    OutPortByte(0xA1, 0x02);
    OutPortByte(0x21, 0x01);
    OutPortByte(0xA1, 0x01);
    OutPortByte(0x21, 0x0);
    OutPortByte(0xA1, 0x0);

    IdtSetGate(0, (uint32_t)Isr0, 0x08, 0x8E);
    IdtSetGate(1, (uint32_t)Isr1, 0x08, 0x8E);
    IdtSetGate(2, (uint32_t)Isr2, 0x08, 0x8E);
    IdtSetGate(3, (uint32_t)Isr3, 0x08, 0x8E);
    IdtSetGate(4, (uint32_t)Isr4, 0x08, 0x8E);
    IdtSetGate(5, (uint32_t)Isr5, 0x08, 0x8E);
    IdtSetGate(6, (uint32_t)Isr6, 0x08, 0x8E);
    IdtSetGate(7, (uint32_t)Isr7, 0x08, 0x8E);
    IdtSetGate(8, (uint32_t)Isr8, 0x08, 0x8E);
    IdtSetGate(9, (uint32_t)Isr9, 0x08, 0x8E);
    IdtSetGate(10, (uint32_t)Isr10, 0x08, 0x8E);
    IdtSetGate(11, (uint32_t)Isr11, 0x08, 0x8E);
    IdtSetGate(12, (uint32_t)Isr12, 0x08, 0x8E);
    IdtSetGate(13, (uint32_t)Isr13, 0x08, 0x8E);
    IdtSetGate(14, (uint32_t)Isr14, 0x08, 0x8E);
    IdtSetGate(15, (uint32_t)Isr15, 0x08, 0x8E);
    IdtSetGate(16, (uint32_t)Isr16, 0x08, 0x8E);
    IdtSetGate(17, (uint32_t)Isr17, 0x08, 0x8E);
    IdtSetGate(18, (uint32_t)Isr18, 0x08, 0x8E);
    IdtSetGate(19, (uint32_t)Isr19, 0x08, 0x8E);
    IdtSetGate(20, (uint32_t)Isr20, 0x08, 0x8E);
    IdtSetGate(21, (uint32_t)Isr21, 0x08, 0x8E);
    IdtSetGate(22, (uint32_t)Isr22, 0x08, 0x8E);
    IdtSetGate(23, (uint32_t)Isr23, 0x08, 0x8E);
    IdtSetGate(24, (uint32_t)Isr24, 0x08, 0x8E);
    IdtSetGate(25, (uint32_t)Isr25, 0x08, 0x8E);
    IdtSetGate(26, (uint32_t)Isr26, 0x08, 0x8E);
    IdtSetGate(27, (uint32_t)Isr27, 0x08, 0x8E);
    IdtSetGate(28, (uint32_t)Isr28, 0x08, 0x8E);
    IdtSetGate(29, (uint32_t)Isr29, 0x08, 0x8E);
    IdtSetGate(30, (uint32_t)Isr30, 0x08, 0x8E);
    IdtSetGate(31, (uint32_t)Isr31, 0x08, 0x8E);
    IdtSetGate(32, (uint32_t)Irq0, 0x08, 0x8E);
    IdtSetGate(33, (uint32_t)Irq1, 0x08, 0x8E);
    IdtSetGate(34, (uint32_t)Irq2, 0x08, 0x8E);
    IdtSetGate(35, (uint32_t)Irq3, 0x08, 0x8E);
    IdtSetGate(36, (uint32_t)Irq4, 0x08, 0x8E);
    IdtSetGate(37, (uint32_t)Irq5, 0x08, 0x8E);
    IdtSetGate(38, (uint32_t)Irq6, 0x08, 0x8E);
    IdtSetGate(39, (uint32_t)Irq7, 0x08, 0x8E);
    IdtSetGate(40, (uint32_t)Irq8, 0x08, 0x8E);
    IdtSetGate(41, (uint32_t)Irq9, 0x08, 0x8E);
    IdtSetGate(42, (uint32_t)Irq10, 0x08, 0x8E);
    IdtSetGate(43, (uint32_t)Irq11, 0x08, 0x8E);
    IdtSetGate(44, (uint32_t)Irq12, 0x08, 0x8E);
    IdtSetGate(45, (uint32_t)Irq13, 0x08, 0x8E);
    IdtSetGate(46, (uint32_t)Irq14, 0x08, 0x8E);
    IdtSetGate(47, (uint32_t)Irq15, 0x08, 0x8E);
    
    IdtFlush((uint32_t)&idtPtr);
}