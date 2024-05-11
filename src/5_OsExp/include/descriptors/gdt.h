#ifndef GDT_H
#define GDT_H

#include "libc/stdint.h"

#define GDT_ENTRIES 5

// Represents a single entry in the Global Descriptor Table. 
// Describes the properties of a segment.
struct _gdtEntry_t {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;                             // Flags to determine what ring the segment can be used in
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed));                      // Packed to let GCC know to not change alignments in the structure.

// Size and address of the GDT.
struct _gdtPtr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


void installGdt();

// Configuration for entries in GDT.
void gdtSetGate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

static struct _gdtEntry_t gdt[GDT_ENTRIES];     // Array of GDT entries
static struct _gdtPtr_t gdtPtr;                 // Pointer to the GDT

#endif