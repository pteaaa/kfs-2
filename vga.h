#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_LIGHT_GREY = 1,
	VGA_COLOR_LIGHT_BLUE = 2,
	VGA_COLOR_LIGHT_GREEN = 3,
	VGA_COLOR_LIGHT_CYAN = 4,
	VGA_COLOR_LIGHT_RED = 5,
	VGA_COLOR_LIGHT_MAGENTA = 6,
	VGA_COLOR_LIGHT_BROWN = 7,
	VGA_COLOR_WHITE = 8,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

#endif
