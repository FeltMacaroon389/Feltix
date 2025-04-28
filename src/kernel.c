#include <stddef.h>
#include <stdint.h>
#include <vga.h>

// Kernel main function
void kernel_main() {

    // Clear screen
    clear_screen();

    // Print ASCII art banner
    print_string("  ___________    .__   __  .__                \n", VGA_COLOR_WHITE);
    print_string("  \\_   _____/___ |  |_/  |_|__|__  ___       \n", VGA_COLOR_WHITE);
    print_string("   |    __)/ __ \\|  |\\   __\\  \\  \\/  /   \n", VGA_COLOR_WHITE);
    print_string("   |     \\  ___/|  |_|  | |  |>    <         \n", VGA_COLOR_WHITE);
    print_string("   \\____/ \\____>____/__| |__/__/\\___\\     \n", VGA_COLOR_WHITE);

    // Print welcome message
    print_string("\n  Welcome to ", VGA_COLOR_WHITE);
    print_string("Feltix!", VGA_COLOR_LIGHT_GREEN);

    print_string("\n    By ", VGA_COLOR_WHITE);
    print_string("FeltMacaroon389", VGA_COLOR_LIGHT_GREY);


    // Return (this shouldn't really happen)
    return;
}

