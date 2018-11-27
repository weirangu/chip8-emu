#include <stdio.h>
#include <stdlib.h>
#include "chip8/reg.h"

// Initializes the registers
void init_reg(chip8_reg* reg){
    reg->pc = 512; // The first instruction is at 512
    reg->index = 0;
    reg->stack_pointer = 0;
}
