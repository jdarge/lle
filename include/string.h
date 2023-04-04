#pragma once

#ifndef SBRK_STRING_H
#define SBRK_STRING_H

#include "def.h"

void *my_memccpy(void *restrict dest, const void *restrict src, int c, size_t n);

void *my_memchr(const void *dest, int i, size_t n);

void *my_memrchr(const void *dest, int i, size_t n);

int my_memcmp(const void *dest, const void *src, size_t n);

void *my_memcpy(void *restrict dest, const void *restrict src, size_t n);

void *my_memmove(void *dest, const void *src, size_t n);

void *my_memset(void *dest, int i, size_t n);

char *my_stpcpy(char *restrict dest, const char *restrict src);

char *my_stpncpy(char *restrict dest, const char *restrict src, size_t n);

char *my_strcat(char *restrict dest, const char *restrict src);

char *my_strchr(const char *str, int c);

int my_strcmp(const char *str1, const char *str2);

char *my_strcpy(char *restrict dest, const char *restrict src);

size_t my_strcspn(const char *str, const char *reject);

char *my_strdup(const char *str);

size_t my_strlen(const char *str);

char *my_strncat(char *restrict dest, const char *restrict src, size_t n);

int my_strncmp(const char *str1, const char *str2, size_t n);

char *my_strncpy(char *restrict dest, const char *restrict src, size_t n);

char *my_strndup(const char *str, size_t n);

size_t my_strnlen(const char *str, size_t maxlen);

char *my_strpbrk(const char *str, const char *accept);

char *my_strrchr(const char *str, int c);

void my_strrev(char *str, int len);

size_t my_strspn(const char *str, const char *accept);

char *my_strtok(char *restrict str, const char *restrict delim);

char *my_strtok_r(char *restrict str, const char *restrict delim, char **restrict saveptr);

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

#endif //SBRK_STRING_H
