#ifndef PAGING_H
#define PAGING_H

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdio.h"

// Mapping virtual to physical address.
extern void PagingMap(uint32_t virtual, uint32_t physical);

void EnablePaging();

extern void InitPaging();

#endif