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
        decrement_timer(sys->timers, beep());

        print(sys->graphics);
    }
}

void cycle(chip8_sys* sys){
    unsigned short pc = sys->reg->pc;
    unsigned char opcode_sig = sys->mem[pc];
    unsigned char opcode_insig = sys->mem[pc + 1];
    printw("opcode_sig = %x \n", opcode_sig);
    printw("opcode_insig = %x \n", opcode_insig);

    // Runs opcode
    ops[(opcode_sig & 0xF0) >> 4](opcode_sig, opcode_insig, sys);
}

void print(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    //clear();

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            for (int k = 1; k != 0x10; k <<= 1){
                // We see the value of each bit and draw if its a 1
                bool bit = graphics[SCREEN_WIDTH][SCREEN_HEIGHT] & k;
                if (bit) {
                    printw("█");
                }
                else {
                    printw(" ");
                }
            }
        }
        printw("\n");
    }

    refresh();
}
