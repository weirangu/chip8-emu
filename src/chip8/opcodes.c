#include <curses.h>
#include <stdlib.h>
#include "chip8/sys.h"
#include "chip8/opcodes.h"

extern WINDOW* curses_win;

void (* ops[0x10])(unsigned char sig, unsigned char insig, chip8_sys* sys) = {
        x0, // 0x0
        x1, // 0x1
        x2, // 0x2
        x3, // 0x3
        x4, // 0x4
        x5, // 0x5
        x6, // 0x6
        x7, // 0x7
        x8, // 0x8
        x9, // 0x9
        xA, // 0xA
        xB, // 0xB
        xC, // 0xC
        xD, // 0xD
        xE, // 0xE
        xF  // 0xF
};

void x0(unsigned char sig, unsigned char insig, chip8_sys* sys){
    if ((sig & 0x0F) == 0x00) {
        if (insig == 0xE0) {
            // 00E0
            for (int i = 0; i < SCREEN_WIDTH; i++) {
                for (int j = 0; j < SCREEN_HEIGHT; j++) {
                    sys->graphics[i][j] = 0;
                }
            }
            increment_pc(sys->reg);
        }
        else {
            //00EE
            unsigned char location = --sys->reg->stack_pointer;
            jump(sys->reg->stack[location], sys->reg);
            increment_pc(sys->reg);
        }
    }
    else {
        // 0NNN
        printw("0NNN Not implemented!");
    }
}

void x1(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 1NNN
    unsigned short mem_location = sig << 8 | insig;
    mem_location &= 0x0FFF;
    jump(mem_location, sys->reg);
}

void x2(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 2NNN
    unsigned short mem_location = sig << 8 | insig;
    mem_location &= 0x0FFF;

    // Stores current location in stack
    sys->reg->stack[sys->reg->stack_pointer++] = sys->reg->pc;

    jump(mem_location, sys->reg);
}

void x3(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 3XNN
    unsigned char x = sig & 0x0F;

    // Skip next instruction
    if (sys->reg->registers[x] == insig) {
        sys->reg->pc += 0x2;
    }
    increment_pc(sys->reg);
}

void x4(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 4XNN
    unsigned char x = sig & 0x0F;

    // Skip next instruction
    if (sys->reg->registers[x] != insig) {
        sys->reg->pc += 0x2;
    }
    increment_pc(sys->reg);
}

void x5(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 5XY0
    unsigned char x = sig & 0x0F;
    unsigned char y = (insig & 0xF0) >> 4;

    // Skip next instruction
    if (sys->reg->registers[x] == sys->reg->registers[y]) {
        sys->reg->pc += 0x2;
    }
    increment_pc(sys->reg);
}

void x6(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 6XNN
    unsigned char reg = sig & 0x0F;
    sys->reg->registers[reg] = insig;
    increment_pc(sys->reg);
}

void x7(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 7XNN
    unsigned char reg = sig & 0x0F;
    sys->reg->registers[reg] += insig;
    increment_pc(sys->reg);
}

void x8(unsigned char sig, unsigned char insig, chip8_sys* sys){
    unsigned char op = insig & 0x0F; // Gives us the last nibble
    unsigned char x = sig & 0x0F;
    unsigned char y = (insig & 0xF0) >> 4;

    unsigned char* reg = sys->reg->registers;

    switch (op) {
        case 0x00:
            reg[x] = reg[y];
            break;
        case 0x01:
            reg[x] |= reg[y];
            break;
        case 0x02:
            reg[x] &= reg[y];
            break;
        case 0x03:
            reg[x] ^= reg[y];
            break;
        case 0x04:
            reg[x] = sum(reg[x], reg[y], reg + 0xF);
            break;
        case 0x05:
            reg[x] = subtract(reg[x], reg[y], reg + 0xF);
            break;
        case 0x06:
            reg[0xF] = reg[x] & 0x01;
            reg[x] >>= 1;
            break;
        case 0x07:
            reg[x] = subtract(reg[y], reg[x], reg + 0xF);
            break;
        case 0x0E:
            reg[0xF] = (reg[x] & 0x80) >> 7;
            reg[x] <<= 1;
            break;
    }
    increment_pc(sys->reg);
}

void x9(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 9XY0
    unsigned char x = sig & 0x0F;
    unsigned char y = (insig & 0xF0) >> 4;

    // Skip next instruction
    if (sys->reg->registers[x] != sys->reg->registers[y]) {
        sys->reg->pc += 0x2;
    }
    increment_pc(sys->reg);
}

void xA(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // ANNN
    unsigned short val = sig << 8 | insig;
    val &= 0x0FFF; // We don't want the most significant nibble
    sys->reg->index = val;
    increment_pc(sys->reg);
}

void xB(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // BNNN
    unsigned short mem_location = sig << 8 | insig;
    mem_location &= 0x0FFF;
    mem_location += sys->reg->registers[0];
    jump(mem_location, sys->reg);
}

void xC(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // CXNN
    unsigned char x = sig & 0x0F;
    sys->reg->registers[x] = (rand() % 256) & insig;
    increment_pc(sys->reg);
}

void xD(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // DXYN
    unsigned char x = sys->reg->registers[sig & 0x0F];
    unsigned char y = sys->reg->registers[(insig & 0xF0) >> 4];
    unsigned char n = insig & 0x0F;
    unsigned short index = sys->reg->index;

    sys->reg->registers[0xF] = 0; // Detects collisions
    for (int i = 0; i < n; i++) { // Loop through the heights
        for (int j = x; j < x + 8; j++) { // Loop over the x values
            unsigned char b = sys->mem[index + i] & 1 << (7 - ((j - x) % 8));
            // Detect if a collision occurred
            if ((sys->graphics[j / 8][y + i] & 1 << (7 - j % 8)) && b) {
                sys->reg->registers[0xF] = 1;
            }
            if (b) // if not b, we don't need to XOR
                sys->graphics[j / 8][y + i] ^= 1 << (7 - j % 8);
        }
    }
    increment_pc(sys->reg);
}

void xE(unsigned char sig, unsigned char insig, chip8_sys* sys){
    unsigned char key = sig & 0x0F;
    switch (insig) {
        // EX9E
        case 0x9E:
            // Skip next instruction if key is pressed
            if (sys->input[key]) {
                sys->reg->pc += 0x02;
            }
            break;
        // EXA1
        case 0xA1:
            // Skip next instruction if key isn't pressed
            if (!sys->input[key]) {
                sys->reg->pc += 0x02;
            }
            break;
        default:
            break;
    }
    increment_pc(sys->reg);
}

void xF(unsigned char sig, unsigned char insig, chip8_sys* sys){
    unsigned char x = sig & 0x0F;

    switch (insig) {
        case 0x07:
            sys->reg->registers[x] = sys->timers->delay_timer;
            break;
        case 0x0A:
            sys->reg->registers[x] = return_input_blocking(curses_win);
            break;
        case 0x15:
            sys->timers->delay_timer = sys->reg->registers[x];
            break;
        case 0x18:
            sys->timers->sound_timer = sys->reg->registers[x];
            break;
        case 0x1E:
            sys->reg->index += sys->reg->registers[x];
            break;
        case 0x29:
            sys->reg->index = sys->reg->registers[x] * 0x5;
            break;
        case 0x33:
            sys->mem[sys->reg->index] = sys->reg->registers[x] / 100; // Most sig digit
            sys->mem[sys->reg->index + 1] = (sys->reg->registers[x] / 10) % 10;
            sys->mem[sys->reg->index + 2] = sys->reg->registers[x] % 10; // Least sig digit
            break;
        case 0x55:
            for (unsigned short i = 0; i < x; i++) {
                sys->mem[sys->reg->index + i] = sys->reg->registers[i];
            }
            break;
        case 0x65:
            for (unsigned short i = 0; i < x; i++) {
                sys->reg->registers[i] = sys->mem[sys->reg->index + i];
            }
            break;
    }
    increment_pc(sys->reg);
}
