#include "builtin.h"
#include "def.h"
#include "print.h"
#include "string.h"

// Write a single character to standard output
void putchar(char c) {
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
void puts(const char *str) {

    if (!str) {
        return;
    }

    size_t len = strlen(str);

    __asm__ __volatile__ (
            "syscall\n\t"
            :
            : "a"(1), "D"(1), "S"(str), "d"(len)
            : "memory"
            );
}

// Write an integer to standard output
void putlong(long n, int width, int type) {
    char str[20]; // Max integer size is 19 digits plus null terminator
    int i = 0;

    // Handle negative numbers
    if (n < 0) {
        putchar('-');
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
    strrev(str, i);

    // Print the number with padding
    int str_len = i;
    while (width > str_len) {
        putchar(' ');
        width--;
    }
    puts(str);
}

// Write a floating-point number to standard output
void putdouble(double num, int width, int type) {

    // Handle negative numbers
    if (num < 0) {
        putchar('-');
        num = -num;
        width--;
    }

    if (width == 0) width = (type == DOUBLE) ? DOUBLE_LENGTH : FLOAT_LENGTH; // todo
    if (type == DOUBLE && width > DOUBLE_LENGTH) width = DOUBLE_LENGTH;
    if (type == FLOAT && width > FLOAT_LENGTH) width = FLOAT_LENGTH;

    // Print integer part
    long int_part = (long) num;
    putlong(int_part, 0, (type == DOUBLE) ? LONG : INT);

    // Print decimal point and fractional part
    num -= (double) int_part;
    if (num > 0) {
        putchar('.');
        for (int i = 0; i < width; ++i) {
            num *= 10;
            putchar((char) ((int) num + '0'));
            num -= (int) num;
        }
    }
}

void vprintf(const char *format, va_list args) {
    char c;
    long n;
    double f;
    const char *s;

    // Parse the format string
    for (size_t i = 0; format[i] != '\0'; ++i) {

        if (format[i] == '!' && format[i + 1] == '%') { // Fix this, it's not safe
            putchar('%');
            i++;
            continue;
        }
        
        if (format[i] != '%') {
            putchar(format[i]);
            continue;
        }
        
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
            c = (char) va_arg(args, int);
            putchar(c);
            break;
        case 's':
            s = va_arg(args, const char*);
            puts(s);
            break;
        case 'd':
        case 'i':
            n = is_long ? va_arg(args, long) : va_arg(args, int);
            putlong(n, width, (is_long) ? LONG : INT);
            break;
        case 'f':
            f = va_arg(args, double); // Floats get promoted
            putdouble(f, width, (is_long) ? DOUBLE : FLOAT);
            break;
        case '\0':
            return;
        default:
            // Unsupported format specifier or width; ignore it
            putchar('%');
            if (is_long) {
                putchar('l');
            }
            putchar(format[i]);
            break;
        }
    }
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

// fix later
void __stack_chk_fail (void) {
    // *(volatile char *)0=0;
    __asm__ __volatile__( "hlt" : : : "memory" );
}
