#pragma once

#ifndef SBRK_DEF_H
#define SBRK_DEF_H

#undef NULL
#define NULL 0

#undef size_t
typedef unsigned long size_t;

#undef uintptr_t
typedef long int intptr_t;

#undef uintptr_t
typedef unsigned long int uintptr_t;

#undef ptrdiff_t
typedef signed long int ptrdiff_t;

#undef wchar_t
typedef int wchar_t;

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *) 0) -> MEMBER)

#endif //SBRK_DEF_H
