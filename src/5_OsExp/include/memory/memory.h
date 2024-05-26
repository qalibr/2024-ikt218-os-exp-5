/* Source: UiA, Per-Arne Lecture/Assignment Assets 

    And,    
    UiA IKT218 2024V
    Group-5 
*/

#ifndef MEMORY_H
#define MEMORY_H

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "system.h"
#include "io/display.h"

typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

void* Malloc(size_t size);   // Allocates memory of a given size
void Free(void *mem);        // Frees allocated memory.

void InitKernelMemory(uint32_t *kernelEnd);
void PrintMemoryLayout();
void PrintMemoryLayoutAtCursor(size_t x, size_t y);

#endif