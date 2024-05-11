#ifndef MEMORY_H
#define MEMORY_H

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "system.h"

typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

void InitKernelMemory(uint32_t *kernelEnd);

void PrintMemoryLayout();

// Allocates memory of a given size and page alignment.
extern char* PMalloc(size_t size);

// Allocates memory of a given size
extern void* Malloc(size_t size);

// Frees allocated memory.
extern void Free(void *mem);
void PFree(void *mem);

#endif