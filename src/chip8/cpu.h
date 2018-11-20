#include <stdio.h>
#include "chip8/cpu.h"

// Initializes the CPU with the given file
// Make sure program is open in r mode
chip8_cpu* init_cpu(FILE* program){
    if (program){
        char c = getc(program);
        while(c != EOF){
            printf("%c\n", c);
            c = getc(program);
        }
    }
    return NULL;
}
