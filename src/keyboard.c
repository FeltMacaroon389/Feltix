// Simple keyboard driver

#include <keyboard.h>

#include <stdint.h>
#include <io.h>

// Function to get a scancode from the keyboard
uint8_t keyboard_get_scancode(void) {
    while (!(inb(0x64) & 0x01)) {
        // Wait until a key is pressed
    }

    return inb(0x60);
}

// Variables to track SHIFT and CAPS LOCK
static int shift_pressed   = 0;
static int capslock_enabled = 0;

// Function to convert a scancode to ASCII
char scancode_to_ascii(uint8_t scancode) {
    // Handle SHIFT key
    if (scancode == 0x2A || scancode == 0x36) {  // Shift pressed
        shift_pressed = 1;

        return 0;
    }
    if (scancode == 0xAA || scancode == 0xB6) {  // Shift released
        shift_pressed = 0;

        return 0;
    }

    // Handle CAPS LOCK
    if (scancode == 0x3A) {
        capslock_enabled = !capslock_enabled;

        return 0;
    }

    // Ignore other break codes
    if (scancode & 0x80)

        return 0;

    // Base mapping, assign a default (unshifted) value
    char character = 0;
    switch (scancode) {

        // Number row
        case 0x02: character = '1'; break;
        case 0x03: character = '2'; break;
        case 0x04: character = '3'; break;
        case 0x05: character = '4'; break;
        case 0x06: character = '5'; break;
        case 0x07: character = '6'; break;
        case 0x08: character = '7'; break;
        case 0x09: character = '8'; break;
        case 0x0A: character = '9'; break;
        case 0x0B: character = '0'; break;

        // Backspace and TAB
        case 0x0E: character = '\b'; break;
        case 0x0F: character = '\t'; break;

        // Symbols beside numbers
        case 0x0C: character = '-'; break;
        case 0x0D: character = '='; break;

        // Top row letters and punctuation
        case 0x10: character = 'q'; break;
        case 0x11: character = 'w'; break;
        case 0x12: character = 'e'; break;
        case 0x13: character = 'r'; break;
        case 0x14: character = 't'; break;
        case 0x15: character = 'y'; break;
        case 0x16: character = 'u'; break;
        case 0x17: character = 'i'; break;
        case 0x18: character = 'o'; break;
        case 0x19: character = 'p'; break;
        case 0x1A: character = '['; break;
        case 0x1B: character = ']'; break;

        // Home row letters and punctuation
        case 0x1E: character = 'a'; break;
        case 0x1F: character = 's'; break;
        case 0x20: character = 'd'; break;
        case 0x21: character = 'f'; break;
        case 0x22: character = 'g'; break;
        case 0x23: character = 'h'; break;
        case 0x24: character = 'j'; break;
        case 0x25: character = 'k'; break;
        case 0x26: character = 'l'; break;
        case 0x27: character = ';'; break;
        case 0x28: character = '\''; break;
        case 0x29: character = ' '; break;

        // Bottom row letters and punctuation
        case 0x2C: character = 'z'; break;
        case 0x2D: character = 'x'; break;
        case 0x2E: character = 'c'; break;
        case 0x2F: character = 'v'; break;
        case 0x30: character = 'b'; break;
        case 0x31: character = 'n'; break;
        case 0x32: character = 'm'; break;
        case 0x33: character = ','; break;
        case 0x34: character = '.'; break;
        case 0x35: character = '/'; break;

        // SPACE and ENTER
        case 0x39: character = ' '; break;
        case 0x1C: character = '\n'; break;

        default:   return 0;
    }

    // Handle SHIFT
    if (shift_pressed) {
        switch (scancode) {
            case 0x02: character = '!'; break;
            case 0x03: character = '@'; break;
            case 0x04: character = '#'; break;
            case 0x05: character = '$'; break;
            case 0x06: character = '%'; break;
            case 0x07: character = '^'; break;
            case 0x08: character = '&'; break;
            case 0x09: character = '*'; break;
            case 0x0A: character = '('; break;
            case 0x0B: character = ')'; break;
            case 0x0C: character = '_'; break;
            case 0x0D: character = '+'; break;
            case 0x1A: character = '{'; break;
            case 0x1B: character = '}'; break;
            case 0x27: character = ':'; break;
            case 0x28: character = '"'; break;
            case 0x29: character = '~'; break;
            case 0x33: character = '<'; break;
            case 0x34: character = '>'; break;
            case 0x35: character = '?'; break;

            default:
                // For letters, we'll adjust below
                break;
        }
    }

    // Handle CAPS LOCK to capitalize letters
    if (character >= 'a' && character <= 'z') {
        if (shift_pressed ^ capslock_enabled) {
            character = character - 'a' + 'A';
        }
    }

    return character;
}

// Wait for a key press and return the corresponding ASCII value
char keyboard_getchar(void) {
    char character = 0;
    while (!character) {
        uint8_t scancode = keyboard_get_scancode();
        character = scancode_to_ascii(scancode);
    }

    return character;
}

