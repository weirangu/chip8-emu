#include "chip8/opcodes.h"

void (*ops[0xF])(unsigned char sig, unsigned char insig) = {
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
    xF  // 0xF
};

void x0(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 0NNN
    // 00E0
    // 00EE
}

void x1(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 1NNN
}

void x2(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 2NNN
}

void x3(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 3XNN
}

void x4(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 4XNN
}

void x5(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 5XY0
}

void x6(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 6XNN
}

void x7(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 7XNN
}

void x8(unsigned char sig, unsigned char insig, chip_8_sys* sys){
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

void x9(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // 9XY0
}

void xA(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // ANNN
    short address = sig << 8 | insig;
    address &= 0x0FFF; // We don't want the most significant nibble
    sys->reg->index = sys->mem[address];
}

void xB(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // BNNN
}

void xC(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // CXNN
}

void xD(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // DXYN
}

void xE(unsigned char sig, unsigned char insig, chip_8_sys* sys){
    // TODO
    // EX9E
    // EXA1
}

void xF(unsigned char sig, unsigned char insig, chip_8_sys* sys){
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

