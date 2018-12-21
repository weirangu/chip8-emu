#include <stdio.h>
#include <malloc.h>
#include "chip8/sys.h"
#include "chip8/reg.h"
#include "chip8/timers.h"

chip8_sys* init_sys(FILE* program){
    chip8_sys* system = malloc(sizeof(chip8_sys));
    system->reg = malloc(sizeof(chip8_reg));
    system->timers = malloc(sizeof(chip8_timers));

    init_reg(system->reg);

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

void print_sys_mem(chip8_sys* sys){
    for (int i = 0; i < 4096; i++){
        printf("%x ", sys->mem[i]);
    }
}
