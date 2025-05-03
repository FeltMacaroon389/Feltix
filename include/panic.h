// Kernel panic handling

#ifndef PANIC_H
#define PANIC_H

#include <vga.h>

// Function to trigger a kernel panic with a custom message
void kernel_panic(const char* message) {

    clear_screen();

    print_string("KERNEL PANIC: ", VGA_COLOR_RED);
    print_string(message, VGA_COLOR_LIGHT_BLUE);

    print_string("\n\nPlease reboot your computer", VGA_COLOR_WHITE);

    // Halt the CPU
    __asm__ __volatile__("hlt");
}

#endif // PANIC_H

