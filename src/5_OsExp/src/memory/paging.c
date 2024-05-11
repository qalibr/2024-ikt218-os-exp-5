#include "memory/paging.h"
#include "libc/string.h"

static uint32_t *pageDirectory = 0;
static uint32_t pageDirLoc = 0;
static uint32_t *lastPage = 0;

void PagingMap(uint32_t virtual, uint32_t physical) {
    uint16_t id = virtual >> 22;    // Upper 10 bits of the virtual address used as index in page dir.

    // Loop over all table entries and set physical address with present and write permissions.
    for (int i = 0; i < 1024; i++) {
        lastPage[i] = physical | 3;
        physical += 4096;
    }

    pageDirectory[id] = ((uint32_t)lastPage) | 3;               // Set page dir entry of this virtual address to the physical address
    lastPage = (uint32_t *)(((uint32_t)lastPage) + 4096);       // Moving to next page.
}


void EnablePaging() {
    asm volatile("mov %%eax, %%cr3": :"a"(pageDirLoc));       // Load the physical address of the page dir into the CR3 reg
    asm volatile("mov %cr0, %eax");                             // Load CR0 register into EAX
    asm volatile("orl $0x80000000, %eax");                      // Setting "enable paging" bit in the EAX reg.
    asm volatile("mov %eax, %cr0");                             // Load the EAX reg into the CR0 register to then enable paging.
}

void InitPaging() {
    printf("Initializing paging...\n");

    pageDirectory = (uint32_t *)0x400000;                       // Page directory starts at 4MB
    pageDirLoc = (uint32_t)pageDirectory;                       // Setting the physical address of the page directory
    lastPage = (uint32_t *)0x404000;                            // Last page starts at 4MB+4KB

    // Loop over the page directory entries
    for (int i = 0; i < 1024; i++) {
        pageDirectory[i] = 0 | 2;
    }

    PagingMap(0, 0);
    PagingMap(0x400000, 0x400000);
    EnablePaging();
    printf("Initialization successful.\n");
}