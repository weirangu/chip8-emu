#include "chip8/timers.h"

void init_timers(chip8_timers* timer){
}

void decrement_timer(chip8_timers* timer, void (*sound) ()){
    if (timer->delay_timer > 0){
        timer->delay_timer--;
    }
    if (timer->sound_timer > 0){
        timer->sound_timer--;
        if (timer->sound_timer == 0){
            sound();
        }
    }
}
