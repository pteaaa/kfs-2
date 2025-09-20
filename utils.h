#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>
#include <stddef.h>

size_t	strlen(const char*);
void kprint(const char*);
void kprint_int(int);
void kprintf(const char* fmt, ...);
void* memcpy(void* dest, const void* src, size_t n);

#endif
