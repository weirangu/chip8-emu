#include <stdio.h>
#include <stdlib.h>
#include "chip8/reg.h"

// Initializes the registers
void init_reg(chip8_reg* reg){
    reg->pc = 512; // The first instruction is at 512
}

void jump(unsigned short mem_location, chip8_reg* reg){
    reg->pc = mem_location;
}
