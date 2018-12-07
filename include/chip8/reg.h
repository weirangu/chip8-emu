#ifndef CHIP8_REG_H
#define CHIP8_REG_H

typedef struct chip8_reg{
    unsigned char registers[0xF];
    unsigned short index;
    unsigned short pc;
    unsigned short stack[24];
    unsigned char stack_pointer;
} chip8_reg;

void init_reg(chip8_reg* program);
#endif
