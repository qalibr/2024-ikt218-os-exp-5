#include "system.h"

void *_impurePtr = NULL;

__attribute__((noreturn)) void Panic(const char*);

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

void Panic(const char* reason) {
    DisplayWrite(reason);
    DisplayWrite("\nHalting system...");

    asm volatile("cli");
    while (true) {
        asm volatile("hlt");
    }
}