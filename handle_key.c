#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "tty.h"
#include "utils.h"
#include "terminal_write.h"
#include "vga.h"
#include "port.h"

void newline() {
	terminal_column = 0;
	terminal_row++;
	terminal_max_column = 0;
	if (terminal_row >= VGA_HEIGHT) {
		terminal_scroll();
		terminal_row = VGA_HEIGHT - 1;
	}
}

void backspace() {
	if (terminal_column > 7) 
			terminal_column--;
	if (terminal_column == 0)
	{
		terminal_putentryat(0, terminal_color, terminal_column, terminal_row);
		terminal_column = VGA_WIDTH - 1;
		terminal_row--;
	}
	terminal_putentryat(0, terminal_color, terminal_column, terminal_row);
}