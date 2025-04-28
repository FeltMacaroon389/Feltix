#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY (uint16_t*)0xB8000

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

// Helper: Create a VGA entry from a character and color
static uint16_t vga_entry(unsigned char uc, vga_color color) {
    return (uint16_t) uc | (uint16_t) (color << 8);
}

// Function to clear the screen and reset the cursor
void clear_screen(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_entry(' ', VGA_COLOR_BLACK); // Fill the screen with black spaces
        }
    }

    // Reset the cursor
    cursor_row = 0;
    cursor_column = 0;
}

// Print a string with the specified color
void print_string(const char* str, vga_color color) {
    while (*str) {
        if (*str == '\n') {
            cursor_column = 0;
            cursor_row++;
        } else {
            const size_t index = cursor_row * VGA_WIDTH + cursor_column;
            vga_buffer[index] = vga_entry((unsigned char)*str, color);
            cursor_column++;
            if (cursor_column >= VGA_WIDTH) {
                cursor_column = 0;
                cursor_row++;
            }
        }
        if (cursor_row >= VGA_HEIGHT) {
            cursor_row = 0; // Wrap back to top (simple wrap behavior)
        }
        str++;
    }
}


#endif // VGA_H

