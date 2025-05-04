#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdlib.h>
#include <vga.h>

// Function to print all accessible memory in megabytes (MB)
void print_accessible_memory() {
    uint32_t total_memory_bytes = 0;
    uint32_t memory_block_size = 1024 * 1024; // Check in 1MB increments
    uint32_t current_address = 0;

    while (1) {
        volatile uint32_t *ptr = (uint32_t *)current_address;

        // Try accessing the memory block
        uint32_t original_value;
        uint32_t test_value = 0xA5A5A5A5;

        // Test read and write access
        __asm__ volatile("" ::: "memory"); // Compiler barrier
        original_value = *ptr;             // Read the original value
        *ptr = test_value;                 // Attempt to write a test value

        // Check if the write succeeded
        if (*ptr == test_value) {
            total_memory_bytes += memory_block_size; // Memory is accessible
            *ptr = original_value;                  // Restore original value
        } else {
            break; // Stop if memory is inaccessible
        }

        current_address += memory_block_size; // Move to the next block
    }

    // Convert bytes to MB
    uint32_t total_memory_mb = total_memory_bytes / (1024 * 1024);

    // Convert the total memory to a string and print it
    char memory_str[16];
    int_to_str(total_memory_mb, memory_str, 0);

    print_string("Accessible memory: ", VGA_COLOR_WHITE);
    print_string(memory_str, VGA_COLOR_LIGHT_GREY);
    print_string("MB\n\n", VGA_COLOR_LIGHT_GREY);
}

#endif // MEMORY_H
//
