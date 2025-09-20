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
#include "terminal_write.h"



size_t terminal_row;
size_t command_line;
size_t terminal_column;
size_t terminal_max_column;
uint8_t terminal_color;
int color = 3;
uint16_t* terminal_buffer;
int cursor_x = 0;
int cursor_y = 1;

// Table pour un clavier QWERTY (sans gestion des majuscules)
unsigned char scancode_to_ascii[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n',  0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',  0, '\\',
    'z','x','c','v','b','n','m',',','.','/',  0, '*',  0, ' ',  0,  0,
    // Suite : touches spéciales non gérées ici
};

/*Terminal utils*/
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_max_column = 0;
	terminal_color = vga_entry_color(color, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_scroll() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_buffer[(y - 1) * VGA_WIDTH + x] = terminal_buffer[y * VGA_WIDTH + x];
        }
    }
    
    /* Effacer la dernière ligne */
    for (int x = 0; x < VGA_WIDTH; x++) {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = (uint16_t) ' ' | (terminal_color << 8);
    }	
}

void move_cursor() {
    uint16_t pos = terminal_row * VGA_WIDTH + terminal_column;

    outb(0x3D4, 0x0F);            // Sélection de la partie basse du curseur
    outb(0x3D5, (uint8_t)(pos & 0xFF));  // Écriture de la partie basse

    outb(0x3D4, 0x0E);            // Sélection de la partie haute du curseur
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));  // Écriture de la partie haute
}

void prompt(uint8_t scancode)
{
	char c;

	c = scancode_to_ascii[scancode];
	switch (scancode) {
		// case 0x48: 
		// 	terminal_writestring("haut");	
		// 	break;
		// case 0x50: 			
		// 	terminal_writestring("bas");
		// 	break;
		case 0x4B: 
			if (terminal_column > 7)
				terminal_column--;
			move_cursor();
			break;
		case 0x4D:
			if (terminal_column < terminal_max_column)
				terminal_column++;
			move_cursor();
			break;
		case 0x3B: 
			if (color > 8)
			{
				color = 1;
				break;
			}
			terminal_color = vga_entry_color(color++, VGA_COLOR_BLACK);
			break;
		case 0x3C: break;
		case 0x3D: break;
		case 0x3E: break;
		case 0x3F: break;
		case 0x40: break;
		case 0x41: break;
		case 0x42: break;
		case 0x43: break;
		case 0x44: break;
		case 0x57: break;
		case 0x58: break;
		default:
			terminal_putchar(c);
			break;
	}
}
