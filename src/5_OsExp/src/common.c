#include "common.h"
#include "libc/stdint.h"

/*
 * SOURCE https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 */

void outPortByte(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inPortByte(uint16_t port) {
    uint8_t ret;

    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint16_t inPortWord(uint16_t port) {
    uint16_t ret;

    asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}