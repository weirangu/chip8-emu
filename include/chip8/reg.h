#ifndef CHIP8_REG_H
#define CHIP8_REG_H

typedef struct chip8_reg{
    unsigned char registers[0x10];
    unsigned short index;
    unsigned short pc;
    unsigned short stack[24];
    unsigned char stack_pointer;
} chip8_reg;

void init_reg(chip8_reg* program);

// Changes pc to mem_location. Does not affect stack.
void jump(unsigned short mem_location, chip8_reg* reg);

// Returns the sum of num1 and num2, and sets the carry accordingly.
unsigned char sum(unsigned char num1, unsigned char num2, unsigned char* carry);

// Returns the difference of num1 and num2, and sets the borrow accordingly.
unsigned char subtract(unsigned char num1, unsigned char num2, unsigned char* borrow);

#endif
