/*
 * SOURCE https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
 */

#ifndef COMMON_H
#define COMMON_H

#include "libc/stdint.h"

void outPortByte(uint16_t port, uint8_t value);     // Sending byte out to specified port
uint8_t inPortByte(uint16_t port);                  // Receiving byte from specified port
uint16_t inPortWord(uint16_t port);                 // Receiving word from specified port

#endif
