#pragma once

#ifndef LLE_SYSTEM_H
#define LLE_SYSTEM_H

#include "def.h"

extern uintptr_t PAGE_SIZE;

long syscall(long num, void *arg);

#endif
