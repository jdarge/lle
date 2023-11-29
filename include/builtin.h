#pragma once

#ifndef LLE_BUILTIN_H
#define LLE_BUILTIN_H

typedef __builtin_va_list va_list;

#define va_start(v, l)   __builtin_va_start(v,l)
#define va_end(v)        __builtin_va_end(v)
#define va_arg(v, l)     __builtin_va_arg(v,l)

#endif
