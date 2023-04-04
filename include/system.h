#pragma once

#ifndef SBRK_SYSTEM_H
#define SBRK_SYSTEM_H

#include "def.h"

extern uintptr_t PAGE_SIZE;

long my_syscall(long num, void *arg);

#endif //SBRK_SYSTEM_H
