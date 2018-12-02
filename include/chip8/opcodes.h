#ifndef CHIP_8_OPCODES_H
#define CHIP_8_OPCODES_H

// A list of pointers that hold functions that process opcodes
// sig is the significant byte, insig is the insignificant byte
void (*ops[0xF])(unsigned char sig, unsigned char insig);

void x0(unsigned char sig, unsigned char insig);
void x1(unsigned char sig, unsigned char insig);
void x2(unsigned char sig, unsigned char insig);
void x3(unsigned char sig, unsigned char insig);
void x4(unsigned char sig, unsigned char insig);
void x5(unsigned char sig, unsigned char insig);
void x6(unsigned char sig, unsigned char insig);
void x7(unsigned char sig, unsigned char insig);
void x8(unsigned char sig, unsigned char insig);
void x9(unsigned char sig, unsigned char insig);
void xA(unsigned char sig, unsigned char insig);
void xB(unsigned char sig, unsigned char insig);
void xC(unsigned char sig, unsigned char insig);
void xD(unsigned char sig, unsigned char insig);
void xE(unsigned char sig, unsigned char insig);
void xF(unsigned char sig, unsigned char insig);
#endif
