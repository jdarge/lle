#include "system.h"

uintptr_t PAGE_SIZE = 4096;

long my_syscall(long num, void *arg) {
    long ret;
    __asm__ __volatile__ (
            "syscall\n"
            : "=a"(ret)
            : "0"(num), "D"(arg)
            : "rcx", "r11", "memory", "cc"
            );
    return ret;
}
