#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdl.h"
#include "chip8/timers.h"

void init_timers(chip8_timers* timer) {
    if (!SDL_AddTimer(TIME_PER_DECREMENT, decrement_timer, timer)) {
        fprintf(stderr, "SDL_AddTimer failed: %s\n", SDL_GetError());
        exit(1);
    }
}

Uint32 decrement_timer(Uint32 interval, void* chip8_timer) {
    chip8_timers* timer = chip8_timer;

    // We want this function to be called again after this function runs
    if (!SDL_AddTimer(TIME_PER_DECREMENT, decrement_timer, timer)) {
        fprintf(stderr, "SDL_AddTimer failed: %s\n", SDL_GetError());
        exit(1);
    }

    if (timer->delay_timer > 0) {
        timer->delay_timer--;
    }
    if (timer->sound_timer > 0) {
        timer->sound_timer--;
        if (timer->sound_timer == 0) {
            beep();
        }
    }
}

void beep(void) {
    SDL_QueueAudio(audio_dev, beep_buffer, beep_length);
}