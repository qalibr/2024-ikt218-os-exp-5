#pragma once

#include "libc/stdint.h"

size_t strlen(const char* str);                                             // Function to calculate the length of a string.
uint8_t *MemCpy(uint8_t *target, const uint8_t *source, size_t bytes);      // Function to copy bytes from source to target memory area
uint8_t *MemSet(uint8_t *target, uint8_t val, size_t bytes);                // Function to set bytes in a memory area to a specific value.
uint16_t *MemSetWord(uint16_t *target, uint16_t val, size_t words);         // Function to set words in a memory area to a specific value
