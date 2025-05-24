#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

void process_command(int argc, char** argv);
void parse_user_input(char* input);
void shell_start(const char* prompt, uint8_t color);

#endif // SHELL_H

