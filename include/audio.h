// Basic PC speaker driver

#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>
#include <io.h>

#define PIT_CHANNEL2     0x42
#define PIT_COMMAND      0x43
#define SPEAKER_CONTROL  0x61

void beep(uint32_t frequency) {
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

void stop_beep() {
    uint8_t tmp = inb(SPEAKER_CONTROL) & 0xFC;
    outb(SPEAKER_CONTROL, tmp); // Clear bits 0 and 1
}

#endif // AUDIO_H

