#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "display.h"
#include "libc/stdio.h"
#include "descriptors/gdt.h"
#include "descriptors/idt.h"
#include "interrupt/isr.h"
#include "pit.h"
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
    InitIrqHandlers();
    InitKernelMemory(&end);
    InitPaging();
    InitDisplay();
    PrintMemoryLayout();
    // Test DisplayWrite
    //DisplayWrite("Hello, World!\n");

    // Test prinft
    //int i = 5;
    //printf("Print 5: %d\n", i + 5);

    // Induce interrupt
    //asm volatile("int $0x3");

    // Allocating memory not using Malloc and inducing page fault
    // uint32_t *ptr = (uint32_t *)0xA0000000;
    // uint32_t do_page_fault = *ptr;

    // Allocating memory using Malloc and inducing page fault
    // void *someMemory = Malloc(12345);
    // void *moreMemory = Malloc(1231234123);

    asm volatile("sti");
    InitPit();

    int counter = 0;

    while (true) {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        SleepBusy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        SleepInterrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    }

    for (;;) ;
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}