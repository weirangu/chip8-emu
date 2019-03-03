#include <stdio.h>
#include <malloc.h>
#include <curses.h>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __linux__
#include <unistd.h>
#endif
#include "chip8/sys.h"
#include "chip8/reg.h"
#include "chip8/timers.h"
#include "chip8/opcodes.h"

chip8_sys* init_sys(FILE* program, WINDOW* curses){
    chip8_sys* system = calloc(1, sizeof(chip8_sys));
    system->reg = calloc(1, sizeof(chip8_reg));
    system->timers = calloc(1, sizeof(chip8_timers));
    system->curses_win = curses;

    init_reg(system->reg);
    init_timers(system->timers);

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
#ifdef _WIN32
        Sleep(1000);
#endif
#ifdef __linux__
        usleep(1000 * 10);
#endif
    }
}

void cycle(chip8_sys* sys){
    run_opcode(sys);

    // Runs opcode
    decrement_timer(sys->timers, beep);
    get_input(sys);
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

void print(unsigned char graphics[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    move(0, 0);

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            for (int k = 0x80; k > 0x00; k >>= 1){
                // We see the value of each bit and draw if its a 1
                int bit = graphics[j][i] & k;
                if (bit) {
                    addch(ACS_BLOCK);
                }
                else {
                    addch('.');
                }
                if (k == 0x00)
                    break; // If we keep right shifting, we stay at 0
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

    // Prints opcode info
    for (int i = 0; i < 64; i++) {
        move(i, SCREEN_WIDTH * 8 + 1);
        printw("%3x \n", sys->prev_ops[i]);
    }
    refresh();
}

void get_input(chip8_sys* sys) {
    // Reset keys
    for (unsigned char i = 0; i < 0x10; i++) {
        sys->input[i] = FALSE;
    }

    int key;
    while ((key = getch()) != ERR){
        sys->input[map_key(key)] = TRUE;
    }
}

int return_input_blocking(WINDOW* win) {
    nodelay(win, FALSE);
    int key = getch();
    nodelay(win, TRUE);
    return map_key(key);
}

int map_key(int key) {
    switch (key) {
        case '1':
            return 0x1;
        case '2':
            return 0x2;
        case '3':
            return 0x3;
        case '4':
            return 0xC;
        case 'q':
            return 0x4;
        case 'w':
            return 0x5;
        case 'e':
            return 0x6;
        case 'r':
            return 0xD;
        case 'a':
            return 0x7;
        case 's':
            return 0x8;
        case 'd':
            return 0x9;
        case 'f':
            return 0xE;
        case 'z':
            return 0xA;
        case 'x':
            return 0x0;
        case 'c':
            return 0xB;
        case 'v':
            return 0xF;
    }
    return -0x1;
}
