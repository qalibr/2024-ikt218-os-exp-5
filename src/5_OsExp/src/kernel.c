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

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    installGdt();
    installIdt();
    initInterruptHandlers();
    initDisplay();
    
    displayWrite("Hello, World!\n");

    int i = 5;
    printf("Print 5: %d\n", i + 5);

    asm volatile("int $0x3");
    
    asm volatile("sti");
    initTimer(50);
    
    for (;;) ;
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}