/*
 * sources: 
 *      https://web.archive.org/web/20190309070619/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
 *      
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "libc/stdint.h"
#include "libc/string.h"
#include "display.h"

typedef struct Registers {
    uint32_t gs, fs, es, ds;                                        // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;    // Affected by 'pusha' in .asm
    uint32_t int_no, err_code;                          // Interrupt number and err code
    uint32_t eip, cs, eflags, useresp, ss;              // Pushed by processor automatically.
} Registers_t;


#endif