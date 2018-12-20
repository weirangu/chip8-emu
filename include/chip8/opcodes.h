#ifndef CHIP_8_OPCODES_H
#define CHIP_8_OPCODES_H

#include "chip8/sys.h"

// A list of pointers that hold functions that process opcodes
// sig is the significant byte, insig is the insignificant byte
void (*ops[0x10])(unsigned char sig, unsigned char insig, chip8_sys *sys);

void x0(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x1(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x2(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x3(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x4(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x5(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x6(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x7(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x8(unsigned char sig, unsigned char insig, chip8_sys* sys);
void x9(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xA(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xB(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xC(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xD(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xE(unsigned char sig, unsigned char insig, chip8_sys* sys);
void xF(unsigned char sig, unsigned char insig, chip8_sys* sys);
#endif
