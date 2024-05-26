/* Source: UiA, Per-Arne Lecture/Assignment Assets 
    
    And,    
    UiA IKT218 2024V
    Group-5 
*/

#include "memory/memory.h"

#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t lastAlloc = 0;     // End of the last alloc
uint32_t heapEnd = 0;       // End address of the heap
uint32_t heapBegin = 0;     // Start address of the heap
uint32_t pheapBegin = 0;    // Page aligned heap
uint32_t pheapEnd = 0;      // Page aligned heap
uint8_t *pheapDesc = 0;     // Descriptor array for page-aligned allocs
uint32_t memoryUsed = 0;    // Total memory used

void* Malloc(size_t size) {
    if (!size) return 0;

    /* This is a memory pointer to the beginning of the heap. It will traverse the heap looking for
        a free block of memory, and failing to find such a block, point to the newly created block. */
    uint8_t *memory = (uint8_t *)heapBegin;

    while ((uint32_t)memory < lastAlloc) {
        alloc_t *allocator = (alloc_t *)memory; // Cast the memory pointer to an alloc_t type, and point it to that structure.
        printf("mem=0x%x, a={.status=%d, .size=%d}\n", memory, allocator->status, allocator->size);

        if (!allocator->size) goto nalloc;  // In the event the allocator is 0, we must create a new memory block
        
        /* Look for available space inside the allocator by traversing it. When the memory pointer encounters
            a block that is already in use (allocator->status = 1), increment the pointer's address and step
            over that block to check out the next. Eventually if all are taken we will have to 'goto nalloc'
            and make a new block of memory. */  
        if (allocator->status) { 
            memory += allocator->size;
            memory += sizeof(alloc_t);
            memory += 4;
            continue;
        }

        // We found a free block of memory, check if the free block is big enough. If it is, allocate memory inside it
        //  and return the pointer to that new block of memory.
        if (allocator->size >= size) {
            allocator->status = 1;
            printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, memory + sizeof(alloc_t), memory + sizeof(alloc_t) + size);
            memset(memory + sizeof(alloc_t), 0, size);
            memoryUsed += size + sizeof(alloc_t);

            return (char *)(memory + sizeof(alloc_t));
        }

        // If the free block was too small, increment over that block like before, and begin the next iteration
        //  of the while-loop.
        memory += allocator->size;
        memory += sizeof(alloc_t);
        memory += 4;
    }
    
    nalloc:;
    if (lastAlloc + size + sizeof(alloc_t) >= heapEnd) {
        Panic("Cannot allocate! Out of memory.\n");
    }

    // Allocate a new block of memory, and return with the pointer to it.
    alloc_t *alloc = (alloc_t *)lastAlloc;
    alloc->status = 1;
    alloc->size = size;

    // Step over the newly allocated memory, and its metadata (4)
    lastAlloc += size;
    lastAlloc += sizeof(alloc_t);
    lastAlloc += 4;
    printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), lastAlloc);

    memoryUsed += size + 4 + sizeof(alloc_t);
    memset((uint8_t *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);

    return (uint8_t *)((uint32_t)alloc + sizeof(alloc_t));
}

void Free(void *mem) {
    alloc_t *alloc = (mem - sizeof(alloc_t));               // Access alloc information by offsetting
    memoryUsed -= alloc->size + sizeof(alloc_t);            // Adjusting memory used tracking
    alloc->status = 0;                                      // Mark this alloc as free
    printf("Freed %d bytes from 0x%x to 0x%x.\n", alloc->size, (uint32_t)mem, (uint32_t)mem + alloc->size);
}

void InitKernelMemory(uint32_t *kernelEnd) {
    lastAlloc = (uint32_t)(kernelEnd + 0x1000);             // Setting lastAlloc to one page after kernel
    heapBegin = lastAlloc;
    
    pheapEnd = 0x400000;
    pheapBegin = pheapEnd - (MAX_PAGE_ALIGNED_ALLOCS * 4096);

    heapEnd = pheapBegin;
    memset((uint8_t*)heapBegin, 0, heapEnd - heapBegin);    // Zero the heap

    pheapDesc = (uint8_t*)Malloc(MAX_PAGE_ALIGNED_ALLOCS);  // Allocating memory for descriptors
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

void PrintMemoryLayoutAtCursor(size_t x, size_t y) {    
    uint32_t memoryFree = heapEnd - heapBegin - memoryUsed;
    uint32_t heapSize = heapEnd - heapBegin;

    const char *descrMemoryUsed = "Memory used: ";
    const char *descrMemoryFree = "Memory free: ";
    const char *descrHeadSize = "Heap size:   ";

    DisplayMoveCursorToLocAndWriteDec(x, y, memoryUsed, descrMemoryUsed);
    DisplayMoveCursorToLocAndWriteDec(x, y + 1, memoryFree, descrMemoryFree);
    DisplayMoveCursorToLocAndWriteDec(x, y + 2, heapSize, descrHeadSize);
}
