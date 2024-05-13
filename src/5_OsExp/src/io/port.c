/* Source: 
- https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html 
- UiA, Per-Arne Lecture/Assignment Assets */


#include "io/port.h"
#include "libc/stdint.h"

void OutPortByte(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t InPortByte(uint16_t port) {
    uint8_t ret;

    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint16_t InPortWord(uint16_t port) {
    uint16_t ret;

    asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}