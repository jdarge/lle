#pragma once

#ifndef SBRK_DEF_H
#define SBRK_DEF_H

#define STDOUT 1

#define SYS_write 1
#define SYS_exit 60

#define NULL 0

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *) 0) -> MEMBER)

typedef unsigned long size_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef signed long int ptrdiff_t;
typedef int wchar_t;

typedef unsigned long long int uint64;

#endif
