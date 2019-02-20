#ifndef CHIP8_TIMERS_H
#define CHIP8_TIMERS_H

typedef struct chip8_timers {
    unsigned char delay_timer;
    unsigned char sound_timer;
} chip8_timers;

// Initializes timers. Assumes timer has been calloced.
void init_timers(chip8_timers* timer);

// Decrements timers. If sound timer reaches 0, sound() is called.
void decrement_timer(chip8_timers* timer, int (*sound) (void));

#endif
