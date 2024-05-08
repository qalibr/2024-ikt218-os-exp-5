#pragma once

#include "libc/stdint.h"

size_t strlen(const char* str);                                         // Function to calculate the length of a string.
uint8_t *memCpy(uint8_t *tar, const uint8_t *src, size_t count);        // Function to copy bytes from source to target memory area
uint8_t *memSet(uint8_t *tar, const uint8_t val, size_t coutn);         // Function to set bytes in a memory area to a specific value.
uint16_t *memSetWord(uint16_t *tar, uint16_t val, size_t count);        // Function to set words in a memory area to a specific value
