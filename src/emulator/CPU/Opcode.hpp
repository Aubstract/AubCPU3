//
// Created by Aubrey on 6/16/2024.
//

#ifndef SOFTCPU2_OPCODE_HPP
#define SOFTCPU2_OPCODE_HPP

// A definition of all the opcodes for the CPU
enum Opcode
{
    HLT = 0,
    JIN,
    CMP,
    ADD,
    SUB,
    AND,
    ORR,
    XOR,
    LSH,
    RSH,
    INC,
    DEC,
    LOD,
    LDI,
    STO,
    CPR
};

#endif //SOFTCPU2_OPCODE_HPP
