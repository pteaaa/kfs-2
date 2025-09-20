#ifndef HANDLE_KEY_H
#define HANDLE_KEY_H

#include <stddef.h>
#include <stdint.h>

void newline();
void backspace();
void handle_key(char c);
void execute_command(char* cmd);

#endif