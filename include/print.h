#pragma once

#ifndef SBRK_PRINT_H
#define SBRK_PRINT_H

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

void my_putchar(char c);

void my_puts(const char *str);

void my_putlong(long n, int width, int type);

void my_putdouble(double num, int width, int type);

void my_printf(const char *format, ...);

void my_vprintf(const char *format, va_list args);

#endif //SBRK_PRINT_H
