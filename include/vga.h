#ifndef VGA_H
#define VGA_H

// VGA-related definitions for convenience
#define VGA_MEMORY 0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

// Function to clear the screen by filling it with black spaces
void clear_screen() {
    unsigned short* vga_buffer = (unsigned short*)VGA_MEMORY;
    unsigned short blank_char = 0x20 | (0x0 << 8);

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        vga_buffer[i] = blank_char;
    }
}

// Function to print a string
void print_string(char *message, short color, int message_length) {
    short *vga = (short *)VGA_MEMORY;
    for (int i = 0; i < message_length; i++) {
        vga[i + SCREEN_WIDTH] = color | message[i];
    }
}

#endif // VGA_H

