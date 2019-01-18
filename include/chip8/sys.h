#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#include <stdio.h>
#include "chip8/reg.h"
#include "chip8/timers.h"

#define SCREEN_WIDTH 8
#define SCREEN_HEIGHT 32

typedef struct chip8_sys {
    unsigned char mem[4096];
    chip8_reg* reg;
    chip8_timers* timers;
    unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT];
    unsigned char input[0x10];
} chip8_sys;

// Initializes the system with a program.
// FILE* program is the CHIP8 ROM that we should load.
chip8_sys* init_sys(FILE* program);

// Prints system memory to printw (needs curses). Does not call refresh.
void print_sys_mem(chip8_sys* sys);

// Runs the system
void run(chip8_sys* sys);

// Runs 1 cycle of the system
void cycle(chip8_sys* sys);

// Prints graphics to the screen (assuming initscr() was called)
void print(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]);

// Prints system info at the sides of the screen (assuming initscr() was called)
void print_sys_info(chip8_sys* sys);

// Gets input from curses
void get_input(chip8_sys* sys);

#endif
