/* Source: UiA, Per-Arne Lecture/Assignment Assets */

#include "system.h"

void *_impurePtr = NULL;

__attribute__((noreturn)) void Panic(const char*);

/* Overrides of stack protector from GCC,
    it prevents code from running when a modification
    to the canary's value changed unexpectedly. */
void __stack_chk_fail_local() {
    Panic("Stack protector: Canary modified");
    __builtin_unreachable();
}
__attribute__((used))
void __stack_chk_fail() {
    Panic("Stack protector: Canary modified");
    __builtin_unreachable();
}
void _exit(int status) {
    char buffer[64] = {};
    printf("Exit called with status %d\n", status);
    Panic("System exit");
    __builtin_unreachable();
}

// Function to handle fatal errors. Use where appropriate, such as
// when allocating memory.
void Panic(const char* reason) {
    DisplayWrite(reason);
    DisplayWrite("\nHalting system...");

    asm volatile("cli");
    while (true) {
        asm volatile("hlt");
    }
}