/* Source: 
- https://medium.com/@noransaber685/creating-a-custom-printf-function-in-c-a-step-by-step-guide-432fd2ecf48a
- https://scientyficworld.org/how-to-write-my-own-printf-in-c/
- https://stackoverflow.com/questions/54352400/implementation-of-printf-function 
- UiA, Per-Arne Lecture/Assignment Assets */

#include "libc/stdarg.h"
#include "libc/stdbool.h"
#include "libc/stdint.h"
#include "io/display.h"
#include "system.h"

int putchar(int ic) {
    char c = (char)ic;
    DisplayPut(c);
    return ic;
}

bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*) data;

    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF) return false;
    }

    return true;
}

int PrintDigit(int value, int base) {
    char buffer[32];
    char *ptr = buffer + sizeof(buffer) - 1;
    *ptr = '\0';

    bool isNegative = value < 0 && base == 10;
    if (isNegative) {
        value = -value; // Flipping the value to positive to simplify the next steps
    }

    while (value != 0) {
        int digit = value % base;
        *--ptr = (digit < 10) ? '0' + digit : 'a' + (digit - 10);
        value /= base;
    }

    if (isNegative) {
        *--ptr = '-';
    }

    return print(ptr, buffer + sizeof(buffer) - ptr - 1);
}

int printf(const char* __restrict__ format, ...) {
    va_list args; // The Variable Arguments list macro is what makes it possible to implement printf
    va_start(args, format);
    int written = 0;

    // Process the format string, handle format specifiers until we encounter the '\0' null terminator.
    while (*format != '\0') {
        if (*format == '%') {
            format++; // Skipping the '%' to read format specifier
            switch (*format) {
                case 'c': {
                    char ch = (char)va_arg(args, int);

                    // Print single char by definiton.
                    if (putchar(ch) == EOF) {
                        va_end(args);
                        return -1;
                    }
                    written++;
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);

                    // Keep putting chars until we reach the end of the string.
                    while (*str) {
                        if (putchar(*str++) == EOF) {
                            va_end(args);
                            return -1;
                        }
                        written++;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    int num = va_arg(args, int);
                    written += PrintDigit(num, 10); 
                    break;
                }
                case 'x': {
                    int hex = va_arg(args, int);
                    written += PrintDigit(hex, 16);
                    break;
                }
                case '%': {
                    // Treating a successive '%' as a literal %, print it.
                    if (putchar('%') == EOF) {
                        va_end(args);
                        return -1;
                    }
                    written++;
                    break;
                }
                default: {
                    // Default action is to print unsupported format specifiers.
                    putchar('%');
                    if (putchar(*format) == EOF) {
                        va_end(args);
                        return -1;
                    }
                    written += 2;
                    break;
                }
            }
        } else {
            // Print characters without specifiers.
            if (putchar(*format) == EOF) {
                va_end(args);
                return -1;
            }
            written++;
        }
        format++; // Proceed to next character
    }

    va_end(args); // Cleanup
    return written;
}