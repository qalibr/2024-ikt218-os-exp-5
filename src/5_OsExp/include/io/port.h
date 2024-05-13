/* Source: 
- https://web.archive.org/web/20190302142203/http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html 
- UiA, Per-Arne Lecture/Assignment Assets */

#ifndef COMMON_H
#define COMMON_H

#include "libc/stdint.h"

// Sending byte out to specified port
void OutPortByte(uint16_t port, uint8_t value);  

// Receiving byte from specified port
uint8_t InPortByte(uint16_t port);          

// Receiving word from specified port
uint16_t InPortWord(uint16_t port);                 

#endif
