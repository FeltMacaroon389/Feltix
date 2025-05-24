// Kernel panic handling

#include <panic.h>

#include <vga.h>
#include <keyboard.h>
#include <power.h>
#include <audio.h>

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

    print_string("\n\n Press any key to reboot...", VGA_COLOR_WHITE);

    // Short beep to get the user's attention
    short_beep();

    // Wait for keypress
    keyboard_getchar();

    // Reboot
    reboot_system();
}

