// Basic VGA text mode driver

#include <vga.h>

#include <stdint.h>
#include <io.h>

// Helper: Create a VGA entry from a character and color
uint16_t vga_entry(unsigned char uc, vga_color color) {
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

// Function to scroll the VGA screen by one line
void scroll(void) {
    // Move each row up one row
    for (size_t row = 1; row < VGA_HEIGHT; row++) {
        for (size_t col = 0; col < VGA_WIDTH; col++) {
            VGA_MEMORY[(row - 1) * VGA_WIDTH + col] = VGA_MEMORY[row * VGA_WIDTH + col];
        }
    }
    // Clear the last row
    for (size_t col = 0; col < VGA_WIDTH; col++) {
        VGA_MEMORY[(VGA_HEIGHT - 1) * VGA_WIDTH + col] = vga_entry(' ', VGA_COLOR_BLACK);
    }
}

// Function to update the hardware cursor
void update_cursor(size_t row, size_t col) {
    uint16_t pos = row * VGA_WIDTH + col;

    outb(0x3D4, 0x0F); // Low byte of cursor
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E); // High byte of cursor
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// Print a single character with the specified color
void print_char(char c, vga_color color) {
    if (c == '\n') {
        cursor_column = 0;
        cursor_row++;
    } else {
        const size_t index = cursor_row * VGA_WIDTH + cursor_column;
        vga_buffer[index] = vga_entry((unsigned char)c, color);
        cursor_column++;
        if (cursor_column >= VGA_WIDTH) {
            cursor_column = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= VGA_HEIGHT) {
        scroll();
        cursor_row = VGA_HEIGHT - 1;
    }

    update_cursor(cursor_row, cursor_column);
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
            scroll();
            cursor_row = VGA_HEIGHT - 1;
        }
        str++;
    }

    update_cursor(cursor_row, cursor_column);
}

// Simple helper to handle a backspace in shell
void shell_backspace(void) {
    if (cursor_column > 0) {
        cursor_column--;

    } else if (cursor_row > 0) {
        cursor_row--;
        cursor_column = VGA_WIDTH - 1;
    }

    VGA_MEMORY[cursor_row * VGA_WIDTH + cursor_column] = vga_entry(' ', VGA_COLOR_BLACK);
}
