// --- FELTIX KERNEL ---

#include <vga.h>
#include <banner.h>
#include <shell.h>

// Kernel main function
void kernel_main() {

    // Clear the screen
    clear_screen();

    // Print white ASCII art banner
    print_banner_white();

    // Print credits
    print_string("\n    By ", VGA_COLOR_WHITE);
    print_string("FeltMacaroon389", VGA_COLOR_LIGHT_GREY);

    // Print welcome message
    print_string("\n\n Welcome to ", VGA_COLOR_WHITE);
    print_string("Feltix!\n", VGA_COLOR_LIGHT_GREEN);

    print_string(" Type ", VGA_COLOR_WHITE);
    print_string("help", VGA_COLOR_CYAN);
    print_string(" for a list of commands!\n\n", VGA_COLOR_WHITE);

    // Hand off control to the shell
    shell_start("Feltix> ", VGA_COLOR_LIGHT_GREEN);

    // Halt the CPU; we're done here
    __asm__ __volatile__("cli; hlt");
}

