#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "display.h"
#include "gdt.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    installGdt();

    //installIdt();

    displayInit(); // Enables writing characters to screen

    displayWrite("Hello, World!");
 
    // __asm__ __volatile__ ("int $0x8");

    for (;;) ;
    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}