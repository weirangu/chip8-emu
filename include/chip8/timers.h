#ifndef CHIP8_TIMERS_H
#define CHIP8_TIMERS_H

#define TIME_PER_DECREMENT 16

typedef struct chip8_timers {
    unsigned char delay_timer;
    unsigned char sound_timer;
} chip8_timers;

// Initializes timers. Assumes timer has been calloced.
void init_timers(chip8_timers* timer);

// Decrements timers (through SDL Timers). If sound timer reaches 0, a beep is made.
Uint32 decrement_timer(Uint32 interval, void* chip8_sys);

// Makes a beep
void beep(void);

#endif
