#include "descriptors/gdt.h"

extern void GdtFlush(uint32_t gdtPtr);

void InstallGdt() {
    gdtPtr.limit = (sizeof(struct gdtEntry_t) * GDT_ENTRIES) - 1;
    gdtPtr.base = (uint32_t) &gdt;

    GdtSetGate(0, 0, 0, 0, 0); // NULL segment
    GdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    GdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    GdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    GdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    GdtFlush((uint32_t) &gdtPtr);
}

void GdtSetGate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {

        // Base addresses in the descriptor, length 32 bits
        gdt[num].baseLow = (base & 0xFFFF); // Lower 16 bits, AND'ing bitmask to preserve 16 bits.
        gdt[num].baseMiddle = (base >> 16) & 0xFF; // Middle 8 bits, AND'ing bitmask to preserve 8 bits, shifted right 16 spaces
        gdt[num].baseHigh = (base >> 24) & 0xFF; // High 8 bits, AND'ing bitmask to preserve 8 bits, shifted right 24 spaces

        // Limits of the descriptor
        gdt[num].limitLow = (limit & 0xFFFF);
        gdt[num].granularity = (limit >> 16) & 0x0F; // High 4 bits of the limit, shifted right 16 spaces

        // Granularity and access flags in the descriptor
        gdt[num].granularity |= granularity & 0xF0; // Granularity 4 bits (upper nibble), OR'ed with gran
        gdt[num].access = access; // Access flags 8 bits
}