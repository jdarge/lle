#pragma once

#ifndef LLE_PRINT_H
#define LLE_PRINT_H

#include "builtin.h"
#include "def.h"

#define LONG 1
#define INT 2
#define DOUBLE 3
#define FLOAT 4

#define INT_LENGTH 6
#define LONG_LENGTH 15
#define DOUBLE_LENGTH 15
#define FLOAT_LENGTH 6

void putchar(char c);

void puts(const char *str);

void putlong(long n, int width, int type);

void putdouble(double num, int width, int type);

void printf(const char *format, ...);

void vprintf(const char *format, va_list args);

void __stack_chk_fail (void);

#endif
