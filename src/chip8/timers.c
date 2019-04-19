#include <time.h>
#include "chip8/timers.h"

void init_timers(chip8_timers* timer){
    timer->next_decrement = TIME_PER_DECREMENT;
}

void decrement_timer(chip8_timers* timer, int (* sound)(void), unsigned int elapsed_time){
    while (elapsed_time >= timer->next_decrement) {
        // We use a while loop just in case 16+ms elapsed, and the timer might need to decrement multiple times
        if (timer->delay_timer > 0){
            timer->delay_timer--;
        }
        if (timer->sound_timer > 0){
            timer->sound_timer--;
            if (timer->sound_timer == 0){
                sound();
            }
        }
        elapsed_time -= timer->next_decrement;
        timer->next_decrement = TIME_PER_DECREMENT;
    }
    // Resets the next_decrement timer, as now elapsed_time < nex_decrement
    timer->next_decrement -= elapsed_time;
}
