#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

uint8_t keyboard_get_scancode(void);
char scancode_to_ascii(uint8_t scancode);
char keyboard_getchar(void);

#endif // KEYBOARD_H

