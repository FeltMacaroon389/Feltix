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
#include <ffs.h>

// Function to process parsed shell commands
void process_command(int argc, char** argv) {

    if (strcmp(argv[0], "help") == 0) {
        print_string("Available commands:\n", VGA_COLOR_WHITE);

        print_string("  help                            ", VGA_COLOR_LIGHT_GREY);
        print_string("- Display this help menu\n", VGA_COLOR_WHITE);

        print_string("  license                         ", VGA_COLOR_LIGHT_GREY);
        print_string("- Display licensing information\n", VGA_COLOR_WHITE);

        print_string("  clear                           ", VGA_COLOR_LIGHT_GREY);
        print_string("- Clear the screen\n", VGA_COLOR_WHITE);

        print_string("  math ", VGA_COLOR_LIGHT_GREY);
        print_string("<num1> <operation> <num2>  ", VGA_COLOR_LIGHT_MAGENTA);
        print_string("- Perform a math operation\n", VGA_COLOR_WHITE);

        print_string("  ls                              ", VGA_COLOR_LIGHT_GREY);
        print_string("- List all files in filesystem\n", VGA_COLOR_WHITE);

        print_string("  touch ", VGA_COLOR_LIGHT_GREY);
        print_string("<filename>                ", VGA_COLOR_LIGHT_MAGENTA);
        print_string("- Create an empty file\n", VGA_COLOR_WHITE);

        print_string("  rm ", VGA_COLOR_LIGHT_GREY);
        print_string("<filename>                   ", VGA_COLOR_LIGHT_MAGENTA);
        print_string("- Delete a file\n", VGA_COLOR_WHITE);

        print_string("  write ", VGA_COLOR_LIGHT_GREY);
        print_string("<filename> <data>         ", VGA_COLOR_LIGHT_MAGENTA);
        print_string("- Write data to a file\n", VGA_COLOR_WHITE);

        print_string("  cat ", VGA_COLOR_LIGHT_GREY);
        print_string("<filename>                  ", VGA_COLOR_LIGHT_MAGENTA);
        print_string("- Display the contents of a file\n", VGA_COLOR_WHITE);

        print_string("  panic                           ", VGA_COLOR_LIGHT_GREY);
        print_string("- Force a kernel panic\n", VGA_COLOR_WHITE);

        print_string("  cpuinfo                         ", VGA_COLOR_LIGHT_GREY);
        print_string("- Display some information about the CPU\n", VGA_COLOR_WHITE);

        print_string("  raminfo                         ", VGA_COLOR_LIGHT_GREY);
        print_string("- Display accessible memory in megabytes\n\n", VGA_COLOR_WHITE);


    } else if (strcmp(argv[0], "license") == 0) {
        print_string("Feltix", VGA_COLOR_LIGHT_GREY);
        print_string(" is licensed under the ", VGA_COLOR_WHITE);
        print_string("GNU GPLv3", VGA_COLOR_LIGHT_GREY);
        print_string(" license\n", VGA_COLOR_WHITE);

        print_string("See the project's ", VGA_COLOR_WHITE);
        print_string("GitHub", VGA_COLOR_LIGHT_GREY);
        print_string(" page for more information:\n\n", VGA_COLOR_WHITE);

        print_string("https://github.com/FeltMacaroon389/Feltix\n\n", VGA_COLOR_LIGHT_BLUE);


    } else if (strcmp(argv[0], "clear") == 0) {
        clear_screen();


    } else if (strcmp(argv[0], "math") == 0) {
        if (argc < 4) {
            print_string("Usage: ", VGA_COLOR_WHITE);
            print_string("math ", VGA_COLOR_LIGHT_GREY);
            print_string("<num1> <operation> <num2>\n\n", VGA_COLOR_LIGHT_MAGENTA);

        } else {
            if (is_valid_float(argv[1]) || is_valid_float(argv[3]) == 1) {
                print_string("Math cannot be performed on non-numbers!\n\n", VGA_COLOR_LIGHT_RED);
                return;
            }

            double num1 = atof(argv[1]);
            double num2 = atof(argv[3]);
            double result;
            char result_buffer[512];

            if (strcmp(argv[2], "+") == 0) {
                result = num1 + num2;

            } else if (strcmp(argv[2], "-") == 0) {
                result = num1 - num2;

            } else if (strcmp(argv[2], "*") == 0) {
                result = num1 * num2;

            } else if (strcmp(argv[2], "/") == 0) {
                if (num2 == 0) {
                    print_string("Division by zero is not allowed!\n\n", VGA_COLOR_LIGHT_RED);
                    return;

                } else {
                    result = num1 / num2;
                }

            } else {
                print_string("Unsupported operation: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[2], VGA_COLOR_LIGHT_GREY);
                print_string("\nSupported operations: ", VGA_COLOR_WHITE);
                print_string("+ - * /\n\n", VGA_COLOR_LIGHT_GREY);
                return;
            }

            int_to_str(result, result_buffer, 0);

            print_string("Result: ", VGA_COLOR_WHITE);
            print_string(result_buffer, VGA_COLOR_LIGHT_GREY);
            print_string("\n", VGA_COLOR_BLACK);
        }


    // Filesystem operations
    } else if (strcmp(argv[0], "ls") == 0) {
        ffs_list_files();


    } else if (strcmp(argv[0], "touch") == 0) {
        if (!argv[1]) {
            print_string("Usage: ", VGA_COLOR_WHITE);
            print_string("touch ", VGA_COLOR_LIGHT_GREY);
            print_string("<filename>\n\n", VGA_COLOR_LIGHT_MAGENTA);

        } else {
            int ffs_return_code = ffs_create_file(argv[1]);

            if (ffs_return_code == FFS_INVALID_NAME) {
                print_string("Filename too long: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);

            } else if (ffs_return_code == FFS_FILE_EXISTS) {
                print_string("File exists: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);

            } else if (ffs_return_code == FFS_NO_SPACE) {
                print_string("No space left. ", VGA_COLOR_LIGHT_RED);
                print_string("Please delete a file to make space", VGA_COLOR_WHITE);
                print_string("\n\n", VGA_COLOR_BLACK);
            }
        }


    } else if (strcmp(argv[0], "rm") == 0) {
        if (!argv[1]) {
            print_string("Usage: ", VGA_COLOR_WHITE);
            print_string("rm ", VGA_COLOR_LIGHT_GREY);
            print_string("<filename>\n\n", VGA_COLOR_LIGHT_MAGENTA);

        } else {
            int ffs_return_code = ffs_delete_file(argv[1]);

           if (ffs_return_code == FFS_FILE_NOT_FOUND) {
                print_string("File not found: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);
            }
        }


    } else if (strcmp(argv[0], "write") == 0) {
        if (argc < 3) {
            print_string("Usage: ", VGA_COLOR_WHITE);
            print_string("write ", VGA_COLOR_LIGHT_GREY);
            print_string("<filename> <data>\n\n", VGA_COLOR_LIGHT_MAGENTA);

        } else {
            // Combine all arguments after argv[1] into a single data string
            char data[4096] = {0};  // Max combined size (4KB)
            for (int i = 2; i < argc; ++i) {
                strcat(data, argv[i]);
                if (i < argc - 1) strcat(data, " ");
            }

            int ffs_return_code = ffs_write_file(argv[1], data);

            if (ffs_return_code == FFS_FILE_NOT_FOUND) {
                print_string("File not found: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);

            } else if (ffs_return_code == FFS_SIZE_EXCEEDS_LIMIT) {
                print_string("File exceeds limit: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);
            }
        }


    } else if (strcmp(argv[0], "cat") == 0) {
        if (!argv[1]) {
            print_string("Usage: ", VGA_COLOR_WHITE);
            print_string("cat ", VGA_COLOR_LIGHT_GREY);
            print_string("<filename>\n\n", VGA_COLOR_LIGHT_MAGENTA);

        } else {
            char cat_buffer[4096];  // 4KB
            size_t cat_buffer_size = sizeof(cat_buffer);

            int ffs_return_code = ffs_read_file(argv[1], cat_buffer, cat_buffer_size);

            if (ffs_return_code == FFS_FILE_NOT_FOUND) {
                print_string("File not found: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);

            } else if (ffs_return_code == FFS_BUFFER_TOO_SMALL) {
                print_string("File too large: ", VGA_COLOR_LIGHT_RED);
                print_string(argv[1], VGA_COLOR_LIGHT_GREY);
                print_string("\n", VGA_COLOR_BLACK);

            } else {
                print_string(cat_buffer, VGA_COLOR_LIGHT_GREY);
                print_string("\n\n", VGA_COLOR_BLACK);
            }
        }


    } else if (strcmp(argv[0], "panic") == 0) {
        kernel_panic("ManuallyTriggeredByUser");


    } else if (strcmp(argv[0], "cpuinfo") == 0) {

        // Print CPU threads
        char* cpu_threads = get_cpu_threads();

        print_string("CPU threads: ", VGA_COLOR_WHITE);
        print_string(cpu_threads, VGA_COLOR_LIGHT_GREY);

        // Print CPU architecture
        print_string("\nCPU architecture: ", VGA_COLOR_WHITE);

        uint32_t is_64bit_supported = cpu_supports_64bit();

        if (is_64bit_supported == 0) {
            print_string("x86\n\n", VGA_COLOR_LIGHT_GREY);

        } else if (is_64bit_supported == 1) {
            print_string("x86_64\n\n", VGA_COLOR_LIGHT_GREY);
        }


    } else if (strcmp(argv[0], "raminfo") == 0) {
        char* memory_mb = get_accessible_memory();

        print_string("Accessible memory: ", VGA_COLOR_WHITE);
        print_string(memory_mb, VGA_COLOR_LIGHT_GREY);
        print_string("MB\n\n", VGA_COLOR_LIGHT_GREY);


    } else {
        print_string("Unknown command: ", VGA_COLOR_LIGHT_RED);
        print_string(argv[0], VGA_COLOR_LIGHT_GREY);
        print_string("\nType ", VGA_COLOR_WHITE);
        print_string("help", VGA_COLOR_CYAN);
        print_string(" for a list of commands\n\n", VGA_COLOR_WHITE);
    }
}

// Function to parse user input
void parse_user_input(char* input) {
    char* argv[64] = { 0 };
    int argc = 0;

    // Split on spaces
    char* token = strtok(input, " ");
    while (token != NULL && argc < 63) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    // Make sure the list is NULL-terminated
    argv[argc] = NULL;

    if (argc > 0) {
        process_command(argc, argv);
    }
}


// Start of shell loop
void shell_start(const char* prompt, uint8_t color) {
    while (1) {

        // Print prompt
        print_string(prompt, color);

        char input_buffer[2048];
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
            parse_user_input(input_buffer);
        }
    }
}

#endif // SHELL_H

