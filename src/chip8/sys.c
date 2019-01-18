#include <stdio.h>
#include <malloc.h>
#include <curses.h>
#include "chip8/sys.h"
#include "chip8/reg.h"
#include "chip8/timers.h"
#include "chip8/opcodes.h"

chip8_sys* init_sys(FILE* program){
    chip8_sys* system = malloc(sizeof(chip8_sys));
    system->reg = malloc(sizeof(chip8_reg));
    system->timers = malloc(sizeof(chip8_timers));

    init_reg(system->reg);

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

void print_sys_mem(chip8_sys* sys){
    for (int i = 0; i < 4096; i++){
        printw("%x ", sys->mem[i]);
    }
}

void run(chip8_sys* sys){
    while (1) {
        cycle(sys);

        print(sys->graphics);
        print_sys_info(sys);
    }
}

void cycle(chip8_sys* sys){
    unsigned short pc = sys->reg->pc;
    unsigned char opcode_sig = sys->mem[pc];
    unsigned char opcode_insig = sys->mem[pc + 1];

    // Runs opcode
    ops[(opcode_sig & 0xF0) >> 4](opcode_sig, opcode_insig, sys);
    decrement_timer(sys->timers, beep);
}

void print(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    move(0, 0);

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            for (int k = 1; k <= 0x80; k <<= 1){
                // We see the value of each bit and draw if its a 1
                bool bit = graphics[i][j] & k;
                if (bit) {
                    addch(ACS_BLOCK);
                }
                else {
                    addch('0');
                }
            }
        }
        addch('\n');
    }

    refresh();
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
    refresh();
}

void get_input(chip8_sys* sys) {
    // Reset keys
    for (unsigned char i = 0; i < 0xF0; i++) {
        sys->input[i] = FALSE;
    }

    int key;
    while ((key = getch()) != ERR){
        // We want to map keyboard keys to the CHIP 8 keypad.
        switch (key) {
            case '1':
                sys->input[0x1] = TRUE;
                break;
            case '2':
                sys->input[0x2] = TRUE;
                break;
            case '3':
                sys->input[0x3] = TRUE;
                break;
            case '4':
                sys->input[0xC] = TRUE;
                break;
            case 'q':
                sys->input[0x4] = TRUE;
                break;
            case 'w':
                sys->input[0x5] = TRUE;
                break;
            case 'e':
                sys->input[0x6] = TRUE;
                break;
            case 'r':
                sys->input[0xD] = TRUE;
                break;
            case 'a':
                sys->input[0x7] = TRUE;
                break;
            case 's':
                sys->input[0x8] = TRUE;
                break;
            case 'd':
                sys->input[0x9] = TRUE;
                break;
            case 'f':
                sys->input[0xE] = TRUE;
                break;
            case 'z':
                sys->input[0xA] = TRUE;
                break;
            case 'x':
                sys->input[0x0] = TRUE;
                break;
            case 'c':
                sys->input[0xB] = TRUE;
                break;
            case 'v':
                sys->input[0xF] = TRUE;
                break;
        }
    }
}
