#include <stddef.h>
#include <stdint.h>
#include <vga.h>

// Kernel main function
void kernel_main() {

    // Clear the screen
    clear_screen();

    // Print ASCII art banner
    // Generated with: https://www.asciiart.eu/text-to-ascii-art
    print_string("   _____    _ _   _              \n", VGA_COLOR_WHITE);
    print_string("  |  ___|__| | |_(_)_  __        \n", VGA_COLOR_WHITE);
    print_string("  | |_ / _ \\ | __| \\ \\/ /     \n", VGA_COLOR_WHITE);
    print_string("  |  _|  __/ | |_| |>  <         \n", VGA_COLOR_WHITE);
    print_string("  |_|  \\___|_|\\__|_/_/\\_\\     \n", VGA_COLOR_WHITE);

    // Print credits
    print_string("\n    By ", VGA_COLOR_WHITE);
    print_string("FeltMacaroon389", VGA_COLOR_LIGHT_GREY);

    // Print welcome message
    print_string("\n\n Welcome to ", VGA_COLOR_WHITE);
    print_string("Feltix!", VGA_COLOR_LIGHT_GREEN);

    // Return (this shouldn't really happen)
    return;
}

