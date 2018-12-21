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
    unsigned char input[0x10];
} chip8_sys;

// Initializes the system with a program.
// FILE* program is the CHIP8 ROM that we should load.
chip8_sys* init_sys(FILE* program);

// Prints system memory.
void print_sys_mem(chip8_sys* sys);

#endif
