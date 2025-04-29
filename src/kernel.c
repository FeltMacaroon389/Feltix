#include <stddef.h>
#include <stdint.h>
#include <vga.h>
#include <banner.h>

// Kernel main function
void kernel_main() {

    // Clear the screen
    clear_screen();

    // Print white ASCII art banner
    // See <include/banner.h>
    print_banner_white();

    // Print credits
    print_string("\n    By ", VGA_COLOR_WHITE);
    print_string("FeltMacaroon389", VGA_COLOR_LIGHT_GREY);

    // Print welcome message
    print_string("\n\n Welcome to ", VGA_COLOR_WHITE);
    print_string("Feltix!", VGA_COLOR_LIGHT_GREEN);

    // Return (this shouldn't really happen)
    return;
}

