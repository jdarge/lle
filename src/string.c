#include "sbrk.h"
#include "string.h"

void strrev(char *str, int len) {
    int start = 0;
    int end = len - 1;
    char temp;
    while (start < end) {
        temp = *(str + start);
        *(str + start) = *(str + end);
        *(str + end) = temp;
        start++;
        end--;
    }
}

void *memccpy(void *restrict dest, const void *restrict src, int c, size_t n) {

    unsigned char *d = (unsigned char *) dest;
    unsigned char *s = (unsigned char *) src;

    while (n-- && (*d++ = *s++) != c);

    if (n) return d + 1;
    return 0;
}

void *memchr(const void *src, int c, size_t n) {

    unsigned char *s = (unsigned char *) src;

    while (n--) {
        if ((unsigned char) c == *s++) {
            return (void *) (s - 1);
        }
    }

    return NULL;
}

void *memrchr(const void *src, int c, size_t n) {

    unsigned char *s = (unsigned char *) src;

    while (n--) {
        if ((unsigned char) c == s[n]) {
            return (void *) (s + n);
        }
    }

    return NULL;
}

int memcmp(const void *mem_p1, const void *mem_p2, size_t n) {

    int ret = 0;

    unsigned char *t_p1 = (unsigned char *) mem_p1;
    unsigned char *t_p2 = (unsigned char *) mem_p2;

    for (; n > 0; n--) {
        if ((ret = *t_p1 - *t_p2)) break;
    }

    return ret;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {

    unsigned char *d = (unsigned char *) dest;
    unsigned char *s = (unsigned char *) src;

    for (size_t i = 0; i < n; i++) {
        *d++ = *s++;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {

    char *d = (char *) dest;
    char *s = (char *) src;

    if (dest <= src) {
        while (n--) *d++ = *s++;
    } else {
        d += n;
        s += n;
        while (n--) *--d = *--s;
    }

    return dest;
}

void *memset(void *mem_p, int i, size_t n) {

    char *p = (char *) mem_p;

    while (n--) *p++ = (char) i;

    return mem_p;
}

char *stpcpy(char *restrict dest, const char *restrict src) {

    while ((*dest++ = *src++));

    return dest - 1;
}

char *stpncpy(char *restrict dest, const char *restrict src, size_t n) {

    while (n-- && (*dest++ = *src++));
    memset(dest, 0, 1);// not sure about this

    return dest;
}

char *strcat(char *restrict dest, const char *restrict src) {

    char *s = dest;

    while (*dest) dest++;
    while ((*dest++ = *src++) != '\0');

    return s;
}

char *strchr(const char *str, int c) {

    while (*str != (char) c) {
        if (*str++ == '\0') return NULL;
    }

    return (char *) str;
}

int strcmp(const char *str1, const char *str2) {

    unsigned char str1__;
    unsigned char str2__;

    do {

        str1__ = *str1++;
        str2__ = *str2++;

        if (str1__ - str2__) break;

    } while (str1__);

    return (str1__ - str2__);
}

char *strcpy(char *restrict dest, const char *restrict src) {

    char *s = dest;

    while ((*dest++ = *src++) != '\0');

    return s;
}

size_t strcspn(const char *str, const char *reject) {

    size_t count = 0;

    for (const char *s = str; *s != '\0'; ++s, ++count) {
        for (const char *r = reject; *r != '\0'; ++r) {
            if (*s == *r) return count;
        }
    }

    return count;
}

char *strdup(const char *str) {

    char *str_new = (char *) sbrk(strlen(str) + 1);

    if (!str_new) return NULL;

    return strcpy(str_new, str);
}

size_t strlen(const char *str) {

    const char *s = str;

    while (*s) s++;

    return s - str;
}

char *strncat(char *restrict dest, const char *restrict src, size_t n) {

    char *s = dest;

    if (!n) return s;

    while (*dest) dest++;
    while ((*dest++ = *src++)) {
        if (--n == 0) {
            *dest = '\0';
            break;
        }
    }

    return s;
}

int strncmp(const char *str1, const char *str2, size_t n) {

    unsigned char str1__;
    unsigned char str2__;

    while (n--) {

        str1__ = *str1++;
        str2__ = *str2++;

        if (str1__ - str2__) {
            return (str1__ < str2__ ? -1 : 1);
        }

        if (!str1__) break;
    }

    return 0;
}

char *strncpy(char *restrict dest, const char *restrict src, size_t n) {

    char *s = dest;

    while (n--) {
        if ((*dest++ = *src++) == '\0') break;
    }

    return s;
}

char *strndup(const char *str, size_t n) {

    size_t s_length = strnlen(str, n);
    char *s = sbrk(s_length + 1);

    if (!s) return NULL;

    memcpy(s, str, s_length);
    s[s_length] = '\0';

    return s;
}

size_t strnlen(const char *str, size_t maxlen) {

    const char *p = memchr(str, 0, maxlen);

    if (p) {
        return p - str;
    }

    return maxlen;
}

char *strpbrk(const char *str, const char *accept) {

    str += strcspn(str, accept);

    if (*str) {
        return (char *) str;
    }

    return NULL;
}

char *strrchr(const char *str, int c) {

    return memrchr(str, c, strlen(str) + 1);
}

size_t strspn(const char *str, const char *accept) {

    size_t count = 0;

    const char *s;
    const char *a;

    for (s = str; *s != '\0'; ++s, ++count) {
        for (a = accept; *a != '\0'; ++a) {
            if (*s == *a) break;
        }

        if (*a == '\0') return count;
    }

    return count;
}

char *strtok(char *restrict str, const char *restrict delim) {

    static char *p;

    if (!str && !(str = p)) return NULL;

    str += strspn(str, delim);
    if (!*str) return NULL;

    p = str + strcspn(str, delim);
    if (*p) *p++ = '\0';
    else p = NULL;

    return str;
}

char *strtok_r(char *restrict str, const char *restrict delim, char **restrict saveptr) {

    if (!str && !(str = *saveptr)) return NULL;

    str += strspn(str, delim);
    if (!*str) return NULL;

    *saveptr = str + strcspn(str, delim);
    if (**saveptr) *(*saveptr)++ = '\0';
    else *saveptr = NULL;

    return str;
}

/*
DESCRIPTION
	The strerror() function returns a pointer to a string that describes the error code passed 
	in the argument errnum, possibly using the LC_MESSAGES part of the current locale to select 
	the appropriate language. (For example, if errnum is EINVAL, the returned description will 
	be "Invalid  argument".) This string must not be modified by the application, but may be 
	modified by a subsequent call to strerror() or strerror_l(). No other library function, 
	including perror(3), will modify this string.

RETURN VALUE
	The strerror() function returns the appropriate error description string, or an "Unknown 
	error nnn" message if the error number is unknown.

	POSIX.1-2001 and POSIX.1-2008 require that a successful call to strerror() shall leave errno 
	unchanged, and note that, since no function return value is reserved to indicate an error, 
	an application that wishes to check for errors should initialize errno to zero before the call,
	and then check errno after the call.
*/
/*char *strerror(int errnum) {// TODO

	return NULL;
}*/

/*
DESCRIPTION
	The strerror_r() function is similar to strerror(), but is thread safe. This function is available 
	in two versions: an XSI-compliant version specified in POSIX.1-2001 (available since glibc 2.3.4, 
	but not POSIX-compliant until glibc 2.13), and a GNU-specific version (available since glibc 2.0). 
	The XSI-compliant version is provided with the feature test macros settings shown in the SYNOPSIS; 
	otherwise the GNU-specific version is provided. If no feature test macros are explicitly defined, 
	then (since glibc 2.4) _POSIX_C_SOURCE is defined by default with the value 200112L, so that the 
	XSI-compliant version of strerror_r() is provided by default.

	The XSI-compliant strerror_r() is preferred for portable applications. It returns the error string 
	in the user-supplied buffer buf of  length  buflen.

	The GNU-specific strerror_r() returns a pointer to a string containing the error message. This may 
	be either a pointer to a string that the function stores in buf, or a pointer to some (immutable) 
	static string (in which case buf is unused). If the function stores a string in buf, then at most 
	buflen bytes are stored (the string may be truncated if buflen is too small and errnum is unknown). 
	The string always includes a terminating null byte ('\0').

RETURN VALUE
	The GNU-specific strerror_r() functions return the appropriate error description string, or an 
	"Unknown error nnn" message if the error number is unknown.

	The  XSI-compliant strerror_r() function returns 0 on success. On error, a (positive) error 
	number is returned (since glibc 2.13), or -1 is returned and errno is set to indicate the 
	error (glibc versions before 2.13).
*/
/*int strerror_r(int errnum, char *buf, size_t buflen) {// TODO

	return 0xDEADBEEF;
}*/

/*
DESCRIPTION
	The strsignal() function returns a string describing the signal number passed in the argument 
	sig. The string can be used only until the next call to strsignal(). The string returned by 
	strsignal() is localized according to the LC_MESSAGES category in the current locale.

RETURN VALUE
	The strsignal() function returns the appropriate description string, or an unknown signal 
	message if the signal number is invalid.
*/
/*char *strsignal(int sig) {// TODO

	return NULL;
}*/

/*
DESCRIPTION
	The strstr() function finds the first occurrence of the substring needle in the string haystack. 
	The terminating null bytes ('\0') are not compared.

RETURN VALUE
	This function returns a pointer to the beginning of the located substring, or NULL if the substring 
	is not found.

	If needle is the empty string, the return value is always haystack itself.
*/
/*char *strstr(const char *haystack, const char *needle) {// TODO

	return NULL;
}*/

/*
DESCRIPTION
	The strxfrm() function transforms the src string into a form such that the result of strcmp(3) 
	on two strings that have been transformed with strxfrm() is the same as the result of strcoll(3)
	on the two strings before their transformation. The first n bytes of the transformed string  are
	placed in dest. The transformation is based on the program's current locale for category LC_COLLATE.

RETURN VALUE
	The strxfrm() function returns the number of bytes required to store the transformed string in dest 
	excluding the terminating null byte ('\0'). If the value returned is n or more, the contents of dest 
	are indeterminate.
*/
/*size_t strxfrm(char *restrict dest, const char *restrict src, size_t n) {// TODO

	return 0xDEADBEEF;
}*/
