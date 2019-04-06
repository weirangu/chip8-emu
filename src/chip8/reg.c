#include <stdio.h>
#include <stdlib.h>
#include "chip8/reg.h"

void init_reg(chip8_reg* reg){
    reg->pc = 512; // The first instruction is at 512
}

void jump(unsigned short mem_location, chip8_reg* reg){
    reg->pc = mem_location;
}

void increment_pc(chip8_reg* reg) {
    reg->pc += 0x2;
}

unsigned char sum(unsigned char num1, unsigned char num2, unsigned char* carry){
    if (num2 > 0xFF - num1) {
        // There will be overflow
        *carry = 1;
    }
    else {
        *carry = 0;
    }

    return num1 + num2;
}

unsigned char subtract(unsigned char num1, unsigned char num2, unsigned char* borrow) {
    if (num2 < num1) {
        // We don't need to borrow
        *borrow = 1;
    }
    else {
        *borrow = 0;
    }

    return num1 - num2;
}
