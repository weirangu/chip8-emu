#ifndef CHIP8_TIMERS_H
#define CHIP8_TIMERS_H

#define TIME_PER_DECREMENT 16

typedef struct chip8_timers {
    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned int next_decrement; // This timer keeps track of the next time the timers are to decrement
} chip8_timers;

// Initializes timers. Assumes timer has been calloced.
void init_timers(chip8_timers* timer);

// Decrements timers. If sound timer reaches 0, sound() is called.
void decrement_timer(chip8_timers* timer, int (* sound)(void), unsigned int elapsed_time);

#endif
