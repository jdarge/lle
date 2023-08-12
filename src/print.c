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

    size_t len = my_strlen(str);

    __asm__ __volatile__ (
            "syscall\n\t"
            :
            : "a"(1), "D"(1), "S"(str), "d"(len)
            : "memory"
            );
}

// Write an integer to standard output
void my_putlong(long n, int width, int type) {
    char str[20]; // Max integer size is 19 digits plus null terminator
    int i = 0;

    // Handle negative numbers
    if (n < 0) {
        my_putchar('-');
        n = -n;
        width--;
    }

    if (type == LONG && width > LONG_LENGTH) width = LONG_LENGTH;
    if (type == INT && width > INT_LENGTH) width = INT_LENGTH;

    // Convert integer to string
    if (n == 0) {
        str[i++] = '0';
    } else {
        while (n > 0) {
            str[i++] = (char) (n % 10 + '0');
            n /= 10;
        }
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string if necessary
    my_strrev(str, i);

    // Print the number with padding
    int str_len = i;
    while (width > str_len) {
        my_putchar(' ');
        width--;
    }
    my_puts(str);
}

// Write a floating-point number to standard output
void my_putdouble(double num, int width, int type) {

    // Handle negative numbers
    if (num < 0) {
        my_putchar('-');
        num = -num;
        width--;
    }

    if (width == 0) width = (type == DOUBLE) ? DOUBLE_LENGTH : FLOAT_LENGTH; // todo
    if (type == DOUBLE && width > DOUBLE_LENGTH) width = DOUBLE_LENGTH;
    if (type == FLOAT && width > FLOAT_LENGTH) width = FLOAT_LENGTH;

    // Print integer part
    long int_part = (long) num;
    my_putlong(int_part, 0, (type == DOUBLE) ? LONG : INT);

    // Print decimal point and fractional part
    num -= (double) int_part;
    if (num > 0) {
        my_putchar('.');
        for (int i = 0; i < width; ++i) {
            num *= 10;
            my_putchar((char) ((int) num + '0'));
            num -= (int) num;
        }
    }
}

void my_vprintf(const char *format, va_list args) {
    char c;
    long n;
    double f;
    const char *s;

    // Parse the format string
    for (size_t i = 0; format[i] != '\0'; ++i) {

        if (format[i] == '!' && format[i + 1] == '%'
                ) { //fix this, not safe
            my_putchar('%');
            i++;
            continue;
        }

        if (format[i] == '%') {

            ++i;  // Skip the '%'

            int is_long = 0;
            if (format[i] == 'l') {
                is_long = 1;
                ++i;  // Skip the 'l'
            }

            // Check for width specifier
            int width = 0;
            while (format[i] >= '0' && format[i] <= '9') {
                width = width * 10 + (format[i] - '0');
                ++i;
            }

            switch (format[i]) {
                case 'c':
                    c = (char) my_va_arg(args, int);
                    my_putchar(c);
                    break;

                case 's':
                    s = my_va_arg(args, const char*);
                    my_puts(s);
                    break;

                case 'd':
                case 'i':
                    n = is_long ? my_va_arg(args, long) : my_va_arg(args, int);
                    my_putlong(n, width, (is_long) ? LONG : INT);
                    break;

                case 'f':
                    f = my_va_arg(args, double); // no need for DOUBLE CHECK ig... floats get promoted?
                    my_putdouble(f, width, (is_long) ? DOUBLE : FLOAT);
                    break;

                case '\0':
                    // End of format string
                    return;

                default:
                    // Unsupported format specifier or width; ignore it.
                    my_putchar('%');
                    if (is_long) {
                        my_putchar('l');
                    }
                    my_putchar(format[i]);
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
