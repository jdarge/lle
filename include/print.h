#pragma once

#ifndef SBRK_PRINT_H
#define SBRK_PRINT_H

#include "builtin.h"
#include "def.h"

void my_putchar(char c);

void my_puts(const char *str);

void my_putint(long n);

void my_putfloat(double num);

void my_printf(const char *format, ...);

void my_vprintf(const char *format, va_list args);

#endif //SBRK_PRINT_H
