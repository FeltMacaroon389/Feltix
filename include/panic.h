// Kernel panic handling

#ifndef PANIC_H
#define PANIC_H

#include <vga.h>

// Function to trigger a kernel panic with a custom message
void kernel_panic(const char* message) {

    clear_screen();

    // Default banner obtained from: https://ascii.co.uk/art/skulls
    print_string("    _____     \n", VGA_COLOR_LIGHT_RED);
    print_string("   /     \\   \n", VGA_COLOR_LIGHT_RED);
    print_string("  | () () |   \n", VGA_COLOR_LIGHT_RED);
    print_string("   \\  ^  /   \n", VGA_COLOR_LIGHT_RED);
    print_string("    |||||     \n", VGA_COLOR_LIGHT_RED);
    print_string("    |||||     \n", VGA_COLOR_LIGHT_RED);

    print_string("\n KERNEL PANIC: ", VGA_COLOR_RED);
    print_string(message, VGA_COLOR_LIGHT_BLUE);

    print_string("\n\n Please reboot your computer", VGA_COLOR_WHITE);

    // Halt the CPU
    __asm__ __volatile__("cli; hlt");
}

#endif // PANIC_H

