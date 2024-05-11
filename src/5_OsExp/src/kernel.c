#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "display.h"
#include "libc/stdio.h"
#include "descriptors/gdt.h"
#include "descriptors/idt.h"
#include "interrupt/isr.h"
#include "timer.h"
#include "memory/memory.h"
#include "memory/paging.h"

extern uint32_t end;

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    InstallGdt();
    InstallIdt();
    InitInterruptHandlers();
    InitKernelMemory(&end);
    InitPaging();
    InitDisplay();
    

    //DisplayWrite("Hello, World!\n");

    //int i = 5;
    //printf("Print 5: %d\n", i + 5);

    //asm volatile("int $0x3");
    
    //asm volatile("sti");
    //InitTimer(50);
    
    PrintMemoryLayout();

    for (;;) ;
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}