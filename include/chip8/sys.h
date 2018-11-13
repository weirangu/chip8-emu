#ifndef CHIP8_SYS_H
#define CHIP8_SYS_H

struct chip8_sys {
    unsigned char mem[4096];
    chip8_cpu cpu;
    chip8_timers timers;
    unsigned char graphics[2048];
    unsigned char input[0xF];
}

#endif CHIP8_SYS_H
