#include "chip8/sys.h"
#include "chip8/opcodes.h"

void (* ops[0x10])(unsigned char sig, unsigned char insig, chip8_sys* sys) = {
        x0, // 0x0
        x1, // 0x1
        x2, // 0x2
        x3, // 0x3
        x4, // 0x4
        x5, // 0x5
        x6, // 0x6
        x7, // 0x7
        x8, // 0x8
        x9, // 0x9
        xA, // 0xA
        xB, // 0xB
        xC, // 0xC
        xD, // 0xD
        xE, // 0xE
        xF  // 0xF
};

void x0(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // 0NNN
    // 00E0
    // 00EE
}

void x1(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 1NNN
    unsigned short mem_location = sig << 8 | insig;
    mem_location &= 0x0FFF;
    jump(mem_location, sys);
}

void x2(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 2NNN
    unsigned short mem_location = sig << 8 | insig;
    mem_location &= 0x0FFF;

    // Stores current location in stack
    sys->reg->stack[sys->reg->stack_pointer + 1] = sys->reg->index;
    sys->reg->stack_pointer++;

    jump(mem_location, sys);
}

void x3(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 3XNN
    unsigned char x = sig & 0x0F;

    // Skip next instruction
    if (sys->reg->registers[x] == insig) {
        sys->reg->pc += 0x1;
    }
}

void x4(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 4XNN
    unsigned char x = sig & 0x0F;

    // Skip next instruction
    if (sys->reg->registers[x] != insig) {
        sys->reg->pc += 0x1;
    }
}

void x5(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 5XY0
    unsigned char x = sig & 0x0F;
    unsigned char y = insig & 0xF0;

    // Skip next instruction
    if (sys->reg->registers[x] == sys->reg->registers[y]) {
        sys->reg->pc += 0x1;
    }
}

void x6(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 6XNN
    unsigned char reg = sig & 0x0F;
    sys->reg->registers[reg] = insig;
}

void x7(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 7XNN
    unsigned char reg = sig & 0x0F;
    sys->reg->registers[reg] += insig;
}

void x8(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // 8XY0
    // 8XY1
    // 8XY2
    // 8XY3
    // 8XY4
    // 8XY5
    // 8XY6
    // 8XY7
    // 8XYE
}

void x9(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // 9XY0
    unsigned char x = sig & 0x0F;
    unsigned char y = insig & 0xF0;

    // Skip next instruction
    if (sys->reg->registers[x] != sys->reg->registers[y]) {
        sys->reg->pc += 0x1;
    }
}

void xA(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // ANNN
    short address = sig << 8 | insig;
    address &= 0x0FFF; // We don't want the most significant nibble
    sys->reg->index = sys->mem[address];
}

void xB(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // BNNN
}

void xC(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // CXNN
}

void xD(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // DXYN
}

void xE(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // EX9E
    // EXA1
}

void xF(unsigned char sig, unsigned char insig, chip8_sys* sys){
    // TODO
    // FX07
    // FX0A
    // FX15
    // FX18
    // FX1E
    // FX29
    // FX33
    // FX55
    // FX65
}

void jump(unsigned short mem_location, const chip8_sys* sys){
    sys->reg->pc = mem_location;
}