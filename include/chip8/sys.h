#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#include <stdio.h>
#include <curses.h>
#include "chip8/reg.h"
#include "chip8/timers.h"

#define SCREEN_WIDTH 8
#define SCREEN_HEIGHT 32

extern WINDOW* curses_win;

typedef struct chip8_sys {
    unsigned char mem[4096];
    chip8_reg* reg;
    chip8_timers* timers;
    unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT];
    unsigned char input[0x10];

    int ms_per_cycle; // How long each cycle takes in ms
    int key_hold_time; // How many cycles a keypress is held for once a keypress is detected

    // Debug vars
    unsigned short prev_ops[64]; // Holds the 64 most recently executed opcodes
} chip8_sys;

// Fonts from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
unsigned char fonts[0x50];

// Initializes the system with a program.
// FILE* program is the CHIP8 ROM that we should load.
// WINDOW* curses is the curses window
chip8_sys* init_sys(FILE* program, int speed, int key_hold_time);

// Runs the system
void run(chip8_sys* sys);

// Runs 1 cycle of the system
void cycle(chip8_sys* sys);

void run_opcode(chip8_sys* sys);

// Prints system info at the sides of the screen (assuming initscr() was called)
void print_sys_info(chip8_sys* sys);

// Gets input from curses
void get_input(chip8_sys* sys);

// Blocks and returns key.
int return_input_blocking(WINDOW* win);

// Maps keyboard input to CHIP8 keypad input.
int map_key(int key);

#endif
