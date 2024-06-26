/* Source: 
- UiA, Per-Arne Lecture/Assignment Assets
- https://web.archive.org/web/20190216040308/http://www.jamesmolloy.co.uk/tutorial_html/5.-IRQs%20and%20the%20PIT.html */

#include "interrupt/isr.h"

// Generic ISR handler that is called when an interrupt is caught.
void IsrHandler(Registers_t r) {
    uint8_t int_no = r.int_no & 0xFF;                                       // Get interrupt code from stack frame
    struct interruptHandler_t interrupt = interruptHandlers[int_no];        // Use interrupt code to find the corresponding interrupt handler

    if (interrupt.handler != 0) {
        interrupt.handler(&r, interrupt.data);
        // printf("PING!\n");
    } else {
        DisplayWrite("Caught interrupt: "); // We come here if an interrupt was not handled by a registered interrupt handler.
        DisplayWriteDec(r.int_no);
        DisplayPut('\n');
        for(;;) ;
    }
}

// Handler for IRQs
void IrqHandler(Registers_t r) {
    // Acknowledge interrupts to the Programmable Interrupt Controler (PIC)
    if (r.int_no >= 40) {
        OutPortByte(0xA0, 0x20);
    }
    OutPortByte(0x20, 0x20);

    struct interruptHandler_t interrupt = irqHandlers[r.int_no];
    if (interrupt.handler != 0) {
        interrupt.handler(&r, interrupt.data);
    }
}

void RegisterInterruptHandler(uint8_t n, isr_t handler, void *context) {
    interruptHandlers[n].handler = handler;
    interruptHandlers[n].data = context;
}

void RegisterIrqHandler(uint8_t irq, isr_t handler, void *context) {
    irqHandlers[irq].handler = handler;
    irqHandlers[irq].data = context;
}

// void InitInterruptHandlers() {
//     MemSet((uint8_t *)&interruptHandlers, 0, sizeof(isr_t)*IDT_ENTRIES);
//     MemSet((uint8_t *)&irqHandlers, 0, sizeof(isr_t)*IRQ_COUNT);
// }

void InitIrqHandlers() {
    for (int i = 0; i < IRQ_COUNT; i++) {
        irqHandlers[i].data = NULL;
        irqHandlers[i].handler = NULL;
        irqHandlers[i].num = i;
    }
}

void InitInterruptHandlers() {
    for (int i = 0; i < IDT_ENTRIES; i++) {
        interruptHandlers[i].data = NULL;
        interruptHandlers[i].handler = NULL;
        interruptHandlers[i].num = i;
    }
}