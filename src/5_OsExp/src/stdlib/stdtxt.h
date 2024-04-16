#ifndef __STDTXT_H
#define __STDTXT_H

#include "stdint.h"
#include "screen.h"

// Function to determine the length of a buffer.
int stringLen(uint8_t *string);

// Standard function for writing text to screen.
void printString(const char *string);

// Implementation of standard printf
// https://cplusplus.com/reference/cstdio/printf/r
int printf( const char * format, ... );

#endif