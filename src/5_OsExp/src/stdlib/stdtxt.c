#include "stdtxt.h"

int stringLen(uint8_t *string)
{
    int i;

    // This loop considers a dereferenced pointer to a string variable and self-terminates when
    // it encounters the null character '\0'
    for (i = 0; *string; string++) {
        i++;
     }

    return i;
}

// TODO: This has no use after printf is implemented. NOTE: It is used currently in splash.c.
void printString(const char *string) {
    putString((uint8_t *) string);
}

int printf( const char * format, ... ) {}