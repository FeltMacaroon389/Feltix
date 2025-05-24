#ifndef AUDIO_H
#define AUDIO_H

#include <stddef.h>
#include <stdint.h>

#define PIT_CHANNEL2     0x42
#define PIT_COMMAND      0x43
#define SPEAKER_CONTROL  0x61

void beep(uint32_t frequency);
void stop_beep(void);
void short_beep(void);

#endif // AUDIO_H

