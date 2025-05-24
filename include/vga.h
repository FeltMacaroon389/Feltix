#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY ((uint16_t*)0xB8000)

static uint16_t* const vga_buffer = VGA_MEMORY;
static size_t cursor_row = 0;
static size_t cursor_column = 0;

// Define VGA colors
typedef enum {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15
} vga_color;

uint16_t vga_entry(unsigned char uc, vga_color color);

void clear_screen(void);
void scroll(void);
void update_cursor(size_t row, size_t col);
void print_char(char c, vga_color color);
void print_string(const char* str, vga_color color);
void shell_backspace(void);

#endif // VGA_H

