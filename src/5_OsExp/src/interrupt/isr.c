#include "interrupt/isr.h"

isr_t interruptHandlers[INT_HANDLERS];

// Generic ISR handler that is called when an interrupt is caught.
void isrHandler(Registers_t r) {
    displayWrite("Caught interrupt: ");
    displayWriteDec(r.int_no);
    displayPut('\n');

    // Check if a specific handler is associated with the interrupt.
    if (interruptHandlers[r.int_no] != 0) {
        isr_t handler = interruptHandlers[r.int_no];
        handler(r);
    }
}

// Handler for IRQs
void irqHandler(Registers_t r) {
    // Acknowledge interrupts to the Programmable Interrupt Controler (PIC)
    if (r.int_no >= 40) outPortByte(0xA0, 0x20);
    outPortByte(0x20, 0x20);

    // Check is a specific handler is associated with the interrupt.
    if (interruptHandlers[r.int_no] != 0) {
        isr_t handler = interruptHandlers[r.int_no];
        handler(r);
    }
}

void registerInterruptHandler(uint8_t n, isr_t handler) {
    interruptHandlers[n] = handler;
}

void initInterruptHandlers() {
    memSet((uint8_t *)&interruptHandlers, 0, sizeof(isr_t)*INT_HANDLERS);
}