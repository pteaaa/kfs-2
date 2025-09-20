#ifndef TERMINAL_WRITE_H
#define TERMINAL_WRITE_H

#include <stddef.h>
#include <stdint.h>

void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);

#endif
