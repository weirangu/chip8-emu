#include <stdio.h>
#include "chip8/sys.h"
#include "chip8/cpu.h"
#include "chip8/timers.h"

// FILE* program is the CHIP8 ROM that we should load.
chip8_sys* init_sys(FILE* program){
    chip8_sys* system = malloc(sizeof(chip8_sys));
    system->cpu = malloc(sizeof(chip8_cpu));
    system->timers = malloc(sizeof(chip8_timers));

    init_cpu(system->cpu);
    // init_timers(system->timers);

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