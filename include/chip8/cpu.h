#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

struct chip8_cpu{
    unsigned char registers[0xF];
    unsigned short index;
    unsigned short pc;
    unsigned short stack[24];
    unsigned char stack_pointer;
}

#endif
