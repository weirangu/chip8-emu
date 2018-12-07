#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#include <stdio.h>
#include "chip8/reg.h"
#include "chip8/timers.h"

typedef struct chip8_sys {
    unsigned char mem[4096];
    chip8_reg* reg;
    chip8_timers* timers;
    unsigned char graphics[2048];
    unsigned char input[0xF];
} chip8_sys;

chip8_sys* init_sys(FILE* program);

void print_sys_mem(chip8_sys* sys);

#endif
