// Basic input handler and command processor

#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vga.h>
#include <keyboard.h>
#include <panic.h>
#include <cpu.h>
#include <memory.h>

// Function to process shell commands
void process_command(char* command) {
    char *args;

    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n", VGA_COLOR_WHITE);
        print_string("  help      - Display this help menu\n", VGA_COLOR_WHITE);
        print_string("  license   - Display licensing information\n", VGA_COLOR_WHITE);
        print_string("  clear     - Clear the screen\n", VGA_COLOR_WHITE);
        print_string("  panic     - Force a kernel panic\n", VGA_COLOR_WHITE);
        print_string("  cpuinfo   - Display some information about the CPU\n", VGA_COLOR_WHITE);
        print_string("  raminfo   - Display accessible memory (RAM) in megabytes (MB)\n\n", VGA_COLOR_WHITE);

    } else if (strcmp(command, "license") == 0) {
        print_string("Feltix", VGA_COLOR_LIGHT_GREY);
        print_string(" is licensed under the ", VGA_COLOR_WHITE);
        print_string("GNU GPLv3", VGA_COLOR_LIGHT_GREY);
        print_string(" license\n", VGA_COLOR_WHITE);
        print_string("See the project's ", VGA_COLOR_WHITE);
        print_string("GitHub", VGA_COLOR_LIGHT_GREY);
        print_string(" page for more information:\n\n", VGA_COLOR_WHITE);
        print_string("https://github.com/FeltMacaroon389/Feltix\n\n", VGA_COLOR_LIGHT_BLUE);

    } else if (strcmp(command, "clear") == 0) {
        clear_screen();

    } else if (strcmp(command, "panic") == 0) {
        kernel_panic("ManuallyTriggeredByUser");

    } else if (strcmp(command, "cpuinfo") == 0) {
        print_cpu_threads();
        print_cpu_mode();

    } else if (strcmp(command, "raminfo") == 0) {
        print_accessible_memory();

    } else {
        print_string("Unknown command. Type ", VGA_COLOR_WHITE);
        print_string("help", VGA_COLOR_CYAN);
        print_string(" for a list of commands.\n\n", VGA_COLOR_WHITE);
    }
}

// Start of shell loop
void shell_start(const char* prompt, uint8_t color) {
    while (1) {

        // Print prompt
        print_string(prompt, color);

        char input_buffer[256];
        size_t input_index = 0;

        // Read characters until ENTER is pressed
        while (1) {

            uint8_t scancode = keyboard_get_scancode();
            char character = scancode_to_ascii(scancode);
            if (!character)
                continue;  // Skip unmapped scancodes

            if (character == '\n') {
                // On newline, print the newline character and break out
                print_string("\n", VGA_COLOR_WHITE);
                break;

            } else if (character == '\b') {
                // Handle backspace, remove last character if available
                if (input_index > 0) {
                    input_index--;
                    shell_backspace();
                }

            } else {
                // Add the character to our input buffer if there is space
                if (input_index < sizeof(input_buffer) - 1) {
                    input_buffer[input_index++] = character;
                    print_char(character, VGA_COLOR_WHITE);
                }
            }
        }

        // Null-terminate the string
        input_buffer[input_index] = '\0';

        if (strcmp(input_buffer, "") != 0) {
            process_command(input_buffer);
        }
    }
}

#endif // SHELL_H

