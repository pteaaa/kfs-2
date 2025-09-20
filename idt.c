#include "port.h"
#include "tty.h"
#include "idt.h"
#include "utils.h"
#include "terminal_write.h"
#include "vga.h"
#include "handle_key.h"

/*Programmable Interrupt Controller*/
#define KEYBOARD_PORT 0x60
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

void pic_init(void) {
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0xFD);
    outb(PIC2_DATA, 0xFF);
}

/*Interrup Descriptor Table*/
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
};

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idt_ptr;

void idt_set_entry(int num, void (*handler)(), uint16_t selector, uint8_t flags) {
	uint32_t base = (uint32_t)handler;
	idt[num].base_low = base & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].selector = selector;
	idt[num].zero = 0;
	idt[num].flags = flags;
}

void keyboard_handler(void) {
    outb(0x20, 0x20);  // Fin de l'IRQ
    unsigned char status = inb(0x64);
    if (status & 0x1)
    {
	    uint8_t scancode = inb(0x60);
	    if (scancode >= 0x80)
		    return;
	    prompt(scancode);
	    if (scancode == 0x1C)
		    terminal_writestring("kfs-1~ ");
    }
}


void idt_init(void) {
	idt_ptr.limit = (sizeof(idt)) - 1;  // Size of the IDT - 1
	idt_ptr.base = (uint32_t) &idt;  // Base address of the IDT
					 //
	idt_set_entry(33, keyboard_handler, 0x08, 0x8E);

	// Load the IDT using the 'lidt' instruction
	__asm__ volatile("lidt (%0)" : : "r" (&idt_ptr));
}

