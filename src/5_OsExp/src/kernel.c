/* Source: UiA, Per-Arne Lecture/Assignment Assets */

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "io/display.h"
#include "libc/stdio.h"
#include "descriptors/gdt.h"
#include "descriptors/idt.h"
#include "interrupt/isr.h"
#include "io/pit.h"
#include "memory/memory.h"
#include "memory/paging.h"
#include "io/keyboard.h"

extern uint32_t end;

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    InstallGdt();                   /* ASSIGNMENT_2.1 */
    InstallIdt();                   /* ASSIGNMENT_3.1 IDT */
    InitInterruptHandlers();        /* ASSIGNMENT_3.2 IRSs */
    InitIrqHandlers();              /* ASSIGNMENT_3.3 IRQs */
    InitKernelMemory(&end);         /* ASSIGNMENT_4 */
    InitPaging();                   /* ASSIGNMENT_4 */ // Paging has no effect.
    InitDisplay();                  /* ASSIGNMENT_2 */
    InitKeyboard();
   
    /* ASSIGNMENT_2.2 Hello, World! */
    // DisplayWrite("Hello, World!\n");
    // printf("Hello, World!");
    // int i = 5;
    // printf("Print 5: %d\n", i + 5);

    /* ASSIGNMENT_3.2 Induce interrupt */
    //asm volatile("int $0x3");

    /* ASSIGNMENT_4.2 PIT */
    asm volatile("sti");    // Must enable interrupts before initializing PIT
    InitPit();              // Init PIT
    // int counter = 0;
    // while (true) {
    //     printf("[%d]: Sleeping with busy-waiting (HIGH CPU)...", ++counter);
    //     SleepBusy(1000);
    //     printf("Slept using busy-waiting.\n");
    //     printf("[%d]: Sleeping with interrupts (LOW CPU)...", ++counter);
    //     SleepInterrupt(1000);
    //     printf("Slept using interrupts.\n");
    //     DisplayClear();
    // }

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}