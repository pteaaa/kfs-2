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

#define CMD_BUF_SIZE 128
char cmd_buffer[CMD_BUF_SIZE];
uint32_t cmd_index = 0;


void execute_command(char* cmd) {
    if (strcmp(cmd, "kfs-2~ printk") == 0) {
		terminal_writestring(" ");
        print_stack();
    }
}

void handle_key(char c) {
    if (c == '\n' || c == '\r') {
        cmd_buffer[cmd_index] = '\0';
        execute_command(cmd_buffer);
        cmd_index = 0;  
    } else if (cmd_index < CMD_BUF_SIZE - 1) {
        cmd_buffer[cmd_index++] = c;
    }
}

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