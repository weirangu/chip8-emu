#ifndef CHIP8_TIMERS_H
#define CHIP8_TIMERS_H

typedef struct chip8_timers {
    unsigned char delay_timer;
    unsigned char sound_timer;
} chip8_timers;

void init_timers(chip8_timers* timer);
#endif
