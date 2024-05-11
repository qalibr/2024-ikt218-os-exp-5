#include "memory/memory.h"

#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t lastAlloc = 0;
uint32_t heapEnd = 0;
uint32_t heapBegin = 0;
uint32_t pheapBegin = 0;
uint32_t pheapEnd = 0;
uint8_t *pheapDesc = 0;
uint32_t memoryUsed = 0;

void InitKernelMemory(uint32_t *kernelEnd) {
    lastAlloc = (uint32_t)(kernelEnd + 0x1000);
    heapBegin = lastAlloc;
    
    pheapEnd = 0x400000;
    pheapBegin = pheapEnd - (MAX_PAGE_ALIGNED_ALLOCS * 4096);

    heapEnd = pheapBegin;
    MemSet((uint8_t*)heapBegin, 0, heapEnd - heapBegin);

    pheapDesc = (uint8_t*)Malloc(MAX_PAGE_ALIGNED_ALLOCS);
    printf("Kernel heap begins at 0x%x\n", lastAlloc);
}

void PrintMemoryLayout() {
    printf("Memory used: %d bytes\n", memoryUsed);
    printf("Memory free: %d bytes\n", heapEnd - heapBegin - memoryUsed);
    printf("Heap size: %d bytes \n", heapEnd - heapBegin);
    printf("Heap start: 0x%x\n", heapBegin);
    printf("Heap end: 0x%x\n", heapEnd);
    printf("PHeap start: 0x%x\nPHeap end: 0x%x\n", pheapBegin, pheapEnd);
}

void Free(void *mem) {
    alloc_t *alloc = (mem - sizeof(alloc_t));
    memoryUsed -= alloc->size + sizeof(alloc_t);
    alloc->status = 0;
}

void PFree(void *mem) {
    uint32_t memory = (uint32_t)mem;                        // Casting pointer
    if (memory < pheapBegin || memory > pheapEnd) return;   // Early return if outside bounds.

    uint32_t id = memory;
    id -= pheapBegin;
    id /= 4096;

    pheapDesc[id] = 0; // Free page descriptor
}

char *PMalloc(size_t size) {
    for (int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++) {
        if (pheapDesc[i]) continue;

        pheapDesc[i] = 1;
        printf("PAllocated from 0x%x to 0x%x\n", pheapBegin + i*4096, pheapBegin + (i + 1) * 4096);
        return (char *)(pheapBegin + i * 4096);        
    }
    printf("PMalloc: FATAL: Failed to allocate!\n");

    return 0;
}

extern void* Malloc(size_t size) {
    if (!size) return 0;

    uint8_t *memory = (uint8_t *)heapBegin;

    while ((uint32_t)memory < lastAlloc) {
        alloc_t *al = (alloc_t *)memory;
        printf("mem=0x%x, a={.status=%d, .size=%d}\n", memory, al->status, al->size);

        if (!al->size) goto nalloc;
        if (al->status) {
            memory += al->size;
            memory += sizeof(alloc_t);
            memory += 4;
            continue;
        }

        if (al->size >= size) {
            al->status = 1;
            printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, memory + sizeof(alloc_t), memory + sizeof(alloc_t) + size);
            MemSet(memory + sizeof(alloc_t), 0, size);
            memoryUsed += size + sizeof(alloc_t);

            return (char *)(memory + sizeof(alloc_t));
        }

        memory += al->size;
        memory += sizeof(alloc_t);
        memory += 4;
    }
    
    nalloc:;
    if (lastAlloc + size + sizeof(alloc_t) >= heapEnd) {
        Panic("Cannot allocate! Out of memory.\n");
    }
    alloc_t *alloc = (alloc_t *)lastAlloc;
    alloc->status = 1;
    alloc->size = size;

    lastAlloc += size;
    lastAlloc += sizeof(alloc_t);
    lastAlloc += 4;
    printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), lastAlloc);

    memoryUsed += size + 4 + sizeof(alloc_t);
    MemSet((uint8_t *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);

    return (uint8_t *)((uint32_t)alloc + sizeof(alloc_t));
}