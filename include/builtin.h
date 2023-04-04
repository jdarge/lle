#pragma once

#ifndef SBRK_BUILTIN_H
#define SBRK_BUILTIN_H

typedef __builtin_va_list va_list;

#define my_va_start(v, l)   __builtin_va_start(v,l)
#define my_va_end(v)       __builtin_va_end(v)
#define my_va_arg(v, l)     __builtin_va_arg(v,l)

#endif //SBRK_BUILTIN_H
