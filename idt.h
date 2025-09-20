#ifndef IDT_H
#define IDT_H

void idt_set_entry(int num, void (*handler)(), uint16_t selector, uint8_t flags);
void idt_init(void);
void pic_init(void);
void keyboard_handler(void);
void set_idt_entry(int index, void (*handler)());
void wait_for_event();

#endif
