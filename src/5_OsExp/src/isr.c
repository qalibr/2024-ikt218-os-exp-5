#include "isr.h"

isr_t interruptHandlers[INT_HANDLERS];

void isrHandler(Registers_t r) {
    displayWrite("Caught interrupt: ");
    displayWriteDec(r.int_no);
    displayPut('\n');

    if (interruptHandlers[r.int_no] != 0) {
        isr_t handler = interruptHandlers[r.int_no];
        handler(r);
    }
}

void irqHandler(Registers_t r) {
    if (r.int_no >= 40) outPortByte(0xA0, 0x20);
    outPortByte(0x20, 0x20);

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