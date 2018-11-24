#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <stdio.h>

typedef struct chip8_cpu{
    unsigned char registers[0xF];
    unsigned short index;
    unsigned short pc;
    unsigned short stack[24];
    unsigned char stack_pointer;
} chip8_cpu;

void init_cpu(chip8_cpu* program);
#endif
