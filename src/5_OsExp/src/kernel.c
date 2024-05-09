#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "display.h"
#include "libc/stdio.h"
#include "gdt.h"
#include "idt.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    installGdt();
    installIdt();

    displayInit(); // Enables writing characters to screen

    displayWrite("Hello, World!");


    int i = 5;

    printf("Print 5: %d", i + 5);
    // TODO: printf

    // asm volatile("int $0x03");
    // __asm__ __volatile__ ("int $0x3");
    //__asm__ __volatile__ ("int $0x4");

    for (;;) ;
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}