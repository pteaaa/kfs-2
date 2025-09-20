#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "port.h"
#include "tty.h"
#include "vga.h"
#include "idt.h"
#include "handle_key.h"
#include "terminal_write.h"
#include "gdt.h"

void kernel_main(void) 
{
	init_gdt();  // Initialisation du GDT
/* Initialize terminal interface */
	terminal_initialize();
	terminal_writestring("ok\n");
	terminal_writestring("\n\n\n\n\n\n\n\n\n\n\n");
	terminal_writestring("                               Hello, welcome!\n");
	terminal_writestring("\n\n\n\n\n\n\n\n\n\n\n");

	pic_init();  // Initialisation du PIC
	idt_init();
	terminal_writestring("kfs-1~ ");
	while (1)
		keyboard_handler();
	return;
}
