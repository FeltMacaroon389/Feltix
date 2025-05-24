// Basic PC speaker driver

#include <audio.h>

#include <stdint.h>
#include <io.h>

// Function to beep the PC speaker at a frequency in MHz
void beep(uint32_t frequency) {

    // Refuse to beep at 0MHz, to prevent a division by zero
    if (frequency == 0) {
        return;
    }

    uint32_t divisor = 1193180 / frequency;

    // Set PIT channel 2 to square wave mode (mode 3)
    outb(PIT_COMMAND, 0xB6); // 1011 0110
    outb(PIT_CHANNEL2, divisor & 0xFF);       // Low byte
    outb(PIT_CHANNEL2, (divisor >> 8) & 0xFF); // High byte

    // Read speaker control
    uint8_t tmp = inb(SPEAKER_CONTROL);

    // Enable speaker (bits 0 and 1)
    if ((tmp & 3) != 3) {
        outb(SPEAKER_CONTROL, tmp | 3);
    }
}

// Function to stop beeping
void stop_beep(void) {
    uint8_t tmp = inb(SPEAKER_CONTROL) & 0xFC;
    outb(SPEAKER_CONTROL, tmp); // Clear bits 0 and 1
}

// Function to execute a quick short beep
void short_beep(void) {
    // Beep to alert the user
    beep(1000);

    // Short delay, as this executes absurdly fast
    int delay = 0;
    while (delay < 3000000) {
        delay++;
    }

    // Stop beeping
    stop_beep();
}

