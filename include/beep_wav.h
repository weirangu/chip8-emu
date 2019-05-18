#ifndef CHIP8_EMU_BEEP_WAV_H
#define CHIP8_EMU_BEEP_WAV_H

// The data of a beep wav file
// Instead of loading the beep wav from a file, we're embedding it into the executable
extern unsigned char beep_wav_data[];
extern int beep_wav_len;

#endif
