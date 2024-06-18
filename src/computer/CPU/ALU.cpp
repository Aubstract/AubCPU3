//
// Created by Aubrey on 6/13/2024.
//

#include "ALU.hpp"

uint16_t ALU::Add(uint8_t a, uint8_t b)
{
    return uint16_t(a) + b;
}

uint16_t ALU::Sub(uint8_t a, uint8_t b)
{
    return uint16_t(a) - b;
}

uint8_t ALU::And(uint8_t a, uint8_t b)
{
    return a & b;
}

uint8_t ALU::Orr(uint8_t a, uint8_t b)
{
    return a | b;
}

uint8_t ALU::Xor(uint8_t a, uint8_t b)
{
    return a ^ b;
}

uint16_t ALU::Lsh(uint8_t a)
{
    return uint16_t(a) << 1;
}

uint8_t ALU::Rsh(uint8_t a)
{
    return a >> 1;
}

uint8_t ALU::Inc(uint8_t a)
{
    return a + 1;
}

uint8_t ALU::Dec(uint8_t a)
{
    return a - 1;
}

uint16_t ALU::Operate(Opcode op, uint8_t a, uint8_t b = 0)
{
    switch (op)
    {
        case ADD:
            return Add(a, b);
        case SUB:
            return Sub(a, b);
        case AND:
            return And(a, b);
        case ORR:
            return Orr(a, b);
        case XOR:
            return Xor(a, b);
        case LSH:
            return Lsh(a);
        case RSH:
            return Rsh(a);
        case INC:
            return Inc(a);
        case DEC:
            return Dec(a);
        default:
            return 0;
    }
}