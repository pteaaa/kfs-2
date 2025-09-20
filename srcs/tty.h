#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

extern size_t terminal_row;
extern size_t command_line;
extern size_t terminal_column;
extern size_t terminal_max_column;
extern uint8_t terminal_color;
extern int color;
extern uint16_t* terminal_buffer;
extern int cursor_x;
extern int cursor_y;
extern unsigned char scancode_to_ascii[128];

void terminal_initialize(void);
void terminal_putchar(char c);
void prompt(uint8_t scancode);
void terminal_scroll();
void move_cursor();
void terminal_setcolor(uint8_t color);

#endif
