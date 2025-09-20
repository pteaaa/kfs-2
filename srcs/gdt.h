#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;     // Lower 16 bits of limit
    uint16_t base_low;      // Lower 16 bits of base
    uint8_t  base_middle;   // Next 8 bits of base
    uint8_t  access;        // Access flags
    uint8_t  flags;   // Granularity and upper 4 bits of limit
    uint8_t  base_high;     // Upper 8 bits of base
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;         // Size of the GDT - 1
    unsigned int base;          // Address of the first gdt_entry
} __attribute__((packed));

void init_gdt();
void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);