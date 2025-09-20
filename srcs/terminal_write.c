#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "tty.h"
#include "utils.h"
#include "vga.h"
#include "port.h"
#include "handle_key.h"

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_putchar(char c) 
{
	handle_key(c);
	if (c == '\n' || terminal_column >= VGA_WIDTH)
		newline();
	else if (c == '\b')
		backspace();
	else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		terminal_column++;
		terminal_max_column = terminal_column;
	}
	move_cursor();
}

