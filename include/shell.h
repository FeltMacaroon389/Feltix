#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include <string.h>
#include <vga.h>
#include <keyboard.h>

// Function to process shell commands
void process_command(char* command) {
    char *args;

    if (strcmp(command, "help") == 0) {
        print_string("Available commands:\n", VGA_COLOR_WHITE);
        print_string("  help      - Display this help menu\n", VGA_COLOR_WHITE);
        print_string("  clear     - Clear the screen\n\n", VGA_COLOR_WHITE);

    } else if (strcmp(command, "clear") == 0) {
        clear_screen();

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

