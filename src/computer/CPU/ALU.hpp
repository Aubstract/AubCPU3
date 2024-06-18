//
// Created by Aubrey on 6/13/2024.
//

#ifndef SOFTCPU2_ALU_HPP
#define SOFTCPU2_ALU_HPP

#include "Opcode.hpp"
#include <cstdint>

class ALU
{
private:
    static uint16_t Add(uint8_t a, uint8_t b);
    static uint16_t Sub(uint8_t a, uint8_t b);
    static uint8_t And(uint8_t a, uint8_t b);
    static uint8_t Orr(uint8_t a, uint8_t b);
    static uint8_t Xor(uint8_t a, uint8_t b);
    static uint16_t Lsh(uint8_t a);
    static uint8_t Rsh(uint8_t a);
    static uint8_t Inc(uint8_t a);
    static uint8_t Dec(uint8_t a);
    
public:
    static uint16_t Operate(Opcode op, uint8_t a, uint8_t b);
};

#endif //SOFTCPU2_ALU_HPP