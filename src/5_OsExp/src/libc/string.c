#include "libc/string.h"
#include "libc/stdint.h"

/*
 * SOURCE: http://www.osdever.net/bkerndev/Docs/creatingmain.htm
 */

size_t strlen(const char* str) {
    size_t len = 0;  // Initialize length variable.

    // Iterate through each character in the string until the null terminator ('\0') is encountered.
    for (; *str != '\0'; str++) {
        len++;
    }

    return len;
}

uint8_t *MemCpy(uint8_t *target, const uint8_t *source, size_t bytes) {
    const char *sourcePtr = (const char *)source;
    char *targetPtr = (char *)target;

    // Copy each byte from source to destination for the specified number of bytes.
    for (; bytes != 0; bytes--) {
        *targetPtr++ = *sourcePtr++;
    }

    return target;
}

uint8_t *MemSet(uint8_t *target, uint8_t val, size_t bytes) {
    char *targetPtr = (char *)target;

    // Set each byte in the target memory to val for the specified number of bytes
    for (; bytes != 0; bytes--) {
        *targetPtr++ = val;
    }

    return target;
}

uint16_t *MemSetWord(uint16_t *target, uint16_t val, size_t words) {
    uint16_t *targetPtr = (uint16_t *)target;

    // Set each word in the target memory to val for the specified number of words.
    for (; words != 0; words--) {
        *targetPtr++ = val;
    }

    return target;
}