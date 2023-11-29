#pragma once

#ifndef LLE_STRING_H
#define LLE_STRING_H

#include "def.h"

void *memccpy(void *restrict dest, const void *restrict src, int c, size_t n);

void *memchr(const void *dest, int i, size_t n);

void *memrchr(const void *dest, int i, size_t n);

int memcmp(const void *dest, const void *src, size_t n);

void *memcpy(void *restrict dest, const void *restrict src, size_t n);

void *memmove(void *dest, const void *src, size_t n);

void *memset(void *dest, int i, size_t n);

char *stpcpy(char *restrict dest, const char *restrict src);

char *stpncpy(char *restrict dest, const char *restrict src, size_t n);

char *strcat(char *restrict dest, const char *restrict src);

char *strchr(const char *str, int c);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *restrict dest, const char *restrict src);

size_t strcspn(const char *str, const char *reject);

char *strdup(const char *str);

size_t strlen(const char *str);

char *strncat(char *restrict dest, const char *restrict src, size_t n);

int strncmp(const char *str1, const char *str2, size_t n);

char *strncpy(char *restrict dest, const char *restrict src, size_t n);

char *strndup(const char *str, size_t n);

size_t strnlen(const char *str, size_t maxlen);

char *strpbrk(const char *str, const char *accept);

char *strrchr(const char *str, int c);

void strrev(char *str, int len);

size_t strspn(const char *str, const char *accept);

char *strtok(char *restrict str, const char *restrict delim);

char *strtok_r(char *restrict str, const char *restrict delim, char **restrict saveptr);

// TODO
//char   *xstrerror(int errnum);
//int     xstrerror_r(int errnum, char *buf, size_t buflen);
//char   *xstrsignal(int sig);
//char   *xstrstr(const char *haystack, const char *needle);v
//size_t  xstrxfrm(char *restrict dest, const char *restrict src, size_t n);

// TO.. LEARN...?
//int     xstrcoll(const char *dest, const char *src);
//int     xstrcoll_l(const char *dest, const char *src, locale_t loc);
//char   *xstrerror_l(int i, locale_t loc);
//size_t  xstrxfrm_l(char *restrict dest, const char *restrict src, size_t n, locale_t loc);

#endif
