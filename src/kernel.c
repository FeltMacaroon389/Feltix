#include <stddef.h>
#include <stdint.h>
#include <vga.h>

// Kernel main function
void kernel_main() {

    // Clear screen and print welcome message
    clear_screen();
    print_string("Welcome to Feltix!", VGA_COLOR_WHITE);

    // Return (this shouldn't really happen)
    return;
}

