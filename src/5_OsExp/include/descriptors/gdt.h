/* Source: https://web.archive.org/web/20190206105749/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html */

#ifndef GDT_H
#define GDT_H

#include "libc/stdint.h"

#define GDT_ENTRIES 5

// Represents a single entry in the Global Descriptor Table. 
// Describes the properties of a segment.
struct gdtEntry_t {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;                             // Flags to determine what ring the segment can be used in
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed));                      // Packed to let GCC know to not change alignments in the structure.

// Size and address of the GDT.
struct gdtPtr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


void InstallGdt();

// Configuration for entries in GDT.
void GdtSetGate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

static struct gdtEntry_t gdt[GDT_ENTRIES];     // Array of GDT entries
static struct gdtPtr_t gdtPtr;                 // Pointer to the GDT

#endif