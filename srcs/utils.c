#include <string.h>
#include <stdarg.h>
#include "tty.h"
#include "terminal_write.h"
#include "vga.h"

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void kprint(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        terminal_putchar(str[i]);
    }
}

// Fonction pour afficher un entier (base 10)
void kprint_int(int value) {
    char buffer[32];
    int i = 0;

    if (value == 0) {
        kprint("0");
        return;
    }

    if (value < 0) {
        kprint("-");
        value = -value;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        terminal_putchar(buffer[j]);
    }
}

void terminal_writehex(unsigned int value) {
    static const char hex_chars[] = "0123456789ABCDEF";
    char buffer[11]; 

    buffer[0] = '0';
    buffer[1] = 'x';

    for (int i = 0; i < 8; i++) {
        unsigned int shift = (7 - i) * 4;
        buffer[2 + i] = hex_chars[(value >> shift) & 0xF];
    }

    buffer[10] = '\0';

    terminal_writestring(buffer);
}




void print_stack() {
    unsigned int *esp;
    asm volatile("mov %%esp, %0" : "=r"(esp));

    terminal_writestring("\n======== Stack dump ==========\n\n");
    for (int i = 0; i < 16; i++) {
        terminal_writehex((unsigned int)(esp + i));
        terminal_writestring(": ");
        terminal_writehex(esp[i]);
        terminal_putchar('\n');
    }
    terminal_writestring("\nEnd of stack dump.\n");
}

void kprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%' && fmt[i+1] != '\0') {
            i++;
            switch (fmt[i]) {
                case 's': {
                    char* str = va_arg(args, char*);
                    kprint(str);
                    break;
                }
                case 'd': {
                    int val = va_arg(args, int);
                    kprint_int(val);
                    break;
                }
                default:
                    terminal_putchar(fmt[i]);
                    break;
            }
        } else {
            terminal_putchar(fmt[i]);
        }
    }

    va_end(args);
}
int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

void* memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
