#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "chip8/reg.h"
#include "chip8/timers.h"

#define SCREEN_WIDTH 8
#define SCREEN_HEIGHT 32

typedef struct {
    unsigned char mem[4096];
    chip8_reg* reg;
    chip8_timers* timers;
    unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT];
    unsigned char input[0x10];

    int blocking_for_key; // Whether the system is blocked waiting for a keypress, -1 indicates a keypress was recieved, but not yet processed
    int most_recent_key; // The most recent keypress
} chip8_sys;

// Fonts from http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
unsigned char fonts[0x50];

// Initializes the system with a program.
chip8_sys* init_sys(FILE* program);

// Runs 1 cycle of the system
void cycle(chip8_sys* sys);

void run_opcode(chip8_sys* sys);

// Input events from SDL
void key_down(chip8_sys* sys, SDL_Keycode keycode);
void key_up(chip8_sys* sys, SDL_Keycode keycode);

// Maps keyboard input to CHIP8 keypad input.
int map_key(SDL_Keycode key);

#endif
