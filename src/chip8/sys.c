#include <stdio.h>
#include <malloc.h>
#include <curses.h>
#include "render.h"
#include "chip8/sys.h"
#include "chip8/reg.h"
#include "chip8/timers.h"
#include "chip8/opcodes.h"

extern int debug;

chip8_sys* init_sys(FILE* program, int speed){
    chip8_sys* system = calloc(1, sizeof(chip8_sys));
    system->reg = calloc(1, sizeof(chip8_reg));
    system->timers = calloc(1, sizeof(chip8_timers));

    init_reg(system->reg);
    init_timers(system->timers);

    system->ms_per_cycle = speed;

    // Load fonts into memory
    for (int i = 0; i < 0x50; i++){
        system->mem[i] = fonts[i];
    }

    // Load program into memory
    if (program){
        short mem_location = 512;
        int c = getc(program);
        while (c != EOF){
            system->mem[mem_location] = c;
            mem_location++; // getc reads in sizeof(c) (which is 8 bytes) at a time
            c = getc(program);
        }
    }
    return system;
}

unsigned char fonts[0x50] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0,
    0x20, 0x60, 0x20, 0x20, 0x70,
    0xF0, 0x10, 0xF0, 0x80, 0xF0,
    0xF0, 0x10, 0xF0, 0x10, 0xF0,
    0x90, 0x90, 0xF0, 0x10, 0x10,
    0xF0, 0x80, 0xF0, 0x10, 0xF0,
    0xF0, 0x80, 0xF0, 0x90, 0xF0,
    0xF0, 0x10, 0x20, 0x40, 0x40,
    0xF0, 0x90, 0xF0, 0x90, 0xF0,
    0xF0, 0x90, 0xF0, 0x10, 0xF0,
    0xF0, 0x90, 0xF0, 0x90, 0x90,
    0xE0, 0x90, 0xE0, 0x90, 0xE0,
    0xF0, 0x80, 0x80, 0x80, 0xF0,
    0xE0, 0x90, 0x90, 0x90, 0xE0,
    0xF0, 0x80, 0xF0, 0x80, 0xF0,
    0xF0, 0x80, 0xF0, 0x80, 0x80
};

void cycle(chip8_sys* sys){
    run_opcode(sys);

    // Runs opcode
    decrement_timer(sys->timers, beep, sys->ms_per_cycle);
}

void run_opcode(chip8_sys* sys) {
    unsigned short pc = sys->reg->pc;
    unsigned char opcode_sig = sys->mem[pc];
    unsigned char opcode_insig = sys->mem[pc + 1];

    ops[(opcode_sig & 0xF0) >> 4](opcode_sig, opcode_insig, sys);
    for (int i = 62; i >= 0; i--) {
        sys->prev_ops[i + 1] = sys->prev_ops[i];
    }
    sys->prev_ops[0] = (opcode_sig << 8) | opcode_insig;
}

void print_sys_info(chip8_sys* sys) {
    move(SCREEN_HEIGHT, 0);

    // Print reg values
    printw("      0x0 0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xA 0xB 0xC 0xD 0xE 0xF x10 x11 x12 x13 x14 x15 x16 x17\n");
    printw("REG   ");
    for (int i = 0; i < 0x10; i++) {
        printw("%3x ", sys->reg->registers[i]);
    }
    addch('\n');

    // Print key values
    printw("KEY   ");
    for (int i = 0; i < 0x10; i++) {
        printw("%3d ", sys->input[i]);
    }
    addch('\n');

    // Print stack values
    printw("STACK ");
    for (int i = 0; i < 0x18; i++) {
        printw("%3x ", sys->reg->stack[i]);
    }
    addch('\n');

    // Print I
    printw("STPTR %3x\n", sys->reg->stack_pointer);

    // Print PC
    printw("PC    %3x\n", sys->reg->pc);

    // Print I
    printw("I     %3x\n", sys->reg->index);

    int maxy = 0; //getmaxy(curses_win); // Gets the maximum y coordinate of the screen
    // Prints opcode info
    move(0, SCREEN_WIDTH * 8 + 6);
    printw("OP\n");
    for (int i = 1; i < ((maxy < 64) ? maxy : 64); i++) {
        move(i, SCREEN_WIDTH * 8 + 6); // We want the opcodes to display to the right of the other info
        printw("%3x \n", sys->prev_ops[i]);
    }
    refresh();
}

void key_down(chip8_sys* sys, SDL_Keycode keycode) {
    int key_mapping = map_key(keycode);
    if (key_mapping >= 0) {
        sys->input[key_mapping] = TRUE;
        sys->most_recent_key = key_mapping;
        if (sys->blocking_for_key) {
            // Tells sys that it should process this key
            sys->blocking_for_key = -1;
        }
    }
}

void key_up(chip8_sys* sys, SDL_Keycode keycode) {
    int key_mapping = map_key(keycode);
    if (key_mapping >= 0) {
        sys->input[key_mapping] = FALSE;
    }
}

int map_key(SDL_Keycode key) {
    switch (key) {
        case SDLK_1:
            return 0x1;
        case SDLK_2:
            return 0x2;
        case SDLK_3:
            return 0x3;
        case SDLK_4:
            return 0xC;
        case SDLK_q:
            return 0x4;
        case SDLK_w:
            return 0x5;
        case SDLK_e:
            return 0x6;
        case SDLK_r:
            return 0xD;
        case SDLK_a:
            return 0x7;
        case SDLK_s:
            return 0x8;
        case SDLK_d:
            return 0x9;
        case SDLK_f:
            return 0xE;
        case SDLK_z:
            return 0xA;
        case SDLK_x:
            return 0x0;
        case SDLK_c:
            return 0xB;
        case SDLK_v:
            return 0xF;
    }
    return -0x1;
}
