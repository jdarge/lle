#include "builtin.h"
#include "def.h"
#include "print.h"
#include "string.h"

// Write a single character to standard output
void my_putchar(char c) {
    __asm__ __volatile__ (
            "mov $1, %%rax\n\t"   // System call number for write
            "mov $1, %%rdi\n\t"   // File descriptor for stdout
            "mov %0, %%rsi\n\t"   // Pointer to the buffer to write
            "mov $1, %%rdx\n\t"   // Number of bytes to write
            "syscall\n\t"         // Call the kernel
            :
            : "g" (&c)
            : "%rax", "%rdi", "%rsi", "%rdx", "memory"
            );
}

// Write a null-terminated string to standard output
void my_puts(const char *str) {

    if (!str) {
        return;
    }

    size_t len = 0;
    const char *p = str;
    while (*p != '\0') {
        ++len;
        ++p;
    }

    __asm__ __volatile__ (
            "syscall\n\t"
            :
            : "a"(1), "D"(1), "S"(str), "d"(len)
            : "memory"
            );
}

// Write an integer to standard output
void my_putint(long n) {
    char str[11]; // Max integer size is 10 digits plus null terminator
    int i = 0;
    do {
        str[i++] = (char) (n % 10 + '0');
        n /= 10;
    } while (n > 0);
    str[i] = '\0';
    my_strrev(str, i); // Reverse the string to get the correct order

    size_t len = 0;
    const char *p = str;
    while (*p != '\0') {
        ++len;
        ++p;
    }
    __asm__ __volatile__ (
            "syscall\n\t"
            :
            : "a"(1), "D"(1), "S"(str), "d"(len)
            : "memory"
            );
}

// Write a floating-point number to standard output
void my_putfloat(double num) {

    char str[20];
    int i = 0;

    // Handle negative numbers
    if (num < 0) {
        str[i++] = '-';
        num = -num;
    }

    // Extract integer and fractional parts
    int integer_part = (int) num;
    float fractional_part = (float) (num - integer_part);

    // Convert integer part to string
    if (integer_part == 0) {
        str[i++] = '0';
    } else {
        while (integer_part != 0) {
            int digit = integer_part % 10;
            str[i++] = (char) (digit + '0');
            integer_part /= 10;
        }
    }

    // Reverse the integer part in the string
    my_strrev(str, i);

    // Add decimal point and convert fractional part to string
    if (fractional_part > 0) {
        str[i++] = '.';
        int decimal_places = 6;
        while (decimal_places-- > 0) {
            fractional_part *= 10;
            int digit = (int) fractional_part;
            str[i++] = (char) (digit + '0');
            fractional_part -= (float) digit;
        }
    }

    // Add null terminator
    str[i] = '\0';

    // Print the string
    my_puts(str);
}

void my_vprintf(const char *format, va_list args) {
    char c;
    long n;
    double f;
    const char *s;

    // Parse the format string
    for (size_t i = 0; format[i] != '\0'; ++i) {
        if (format[i] == '%') {
            ++i;  // Skip the '%'

            int is_long = 0;
            if (format[i] == 'l') {
                is_long = 1;
                ++i;  // Skip the 'l'
            }

            switch (format[i]) {
                case 'c':
                    c = (char) my_va_arg(args,
                    int);
                    my_putchar(c);
                    break;

                case 's':
                    s = my_va_arg(args,
                    const char*);
                    my_puts(s);
                    break;

                case 'd':
                case 'i':
                    n = is_long ? my_va_arg(args,
                    long) : my_va_arg(args,
                    int);
                    my_putint(n);
                    break;

                case 'f':
                    f = my_va_arg(args,
                    double);
                    my_putfloat(f);
                    break;

                default:
                    // Unsupported format specifier; ignore it.
                    break;
            }
        } else {
            my_putchar(format[i]);
        }
    }
}

void my_printf(const char *format, ...) {
    va_list args;
    my_va_start(args, format);
    my_vprintf(format, args);
    my_va_end(args);
}
