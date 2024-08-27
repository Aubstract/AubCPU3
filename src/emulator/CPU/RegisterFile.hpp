//
// Created by Aubrey on 6/13/2024.
//

#ifndef SOFTCPU2_REGISTERFILE_HPP
#define SOFTCPU2_REGISTERFILE_HPP

#ifndef NDEBUG
    #include "../log/log.hpp"
    #include <iomanip>
#endif

#include "Memory.hpp"
#include <cstdint>
#include <cassert>
#include <iostream>

// Defines the bit index for each flag
enum FlagAddr
{
    zero = 0,
    not_zero,
    carry_out,
    sign_bit,
    overflow,
    signed_less_than,
    FLAG_ADDR_MAX = signed_less_than
};

// Defines addresses for the special registers
inline constexpr uint8_t HARDWIRE_ZERO_ADDR = 0;
inline constexpr uint8_t FLAG_REG_ADDR = 13;
inline constexpr uint8_t STACK_PTR_ADDR = 14;
inline constexpr uint8_t PROG_CNTR_ADDR = 15;
inline constexpr size_t REG_FILE_SIZE = 16;

// The RegisterFile class represents all the registers of the computer that can be used as an operand in instructions.
// Since some of those registers are a little irregular in their meaning/behavior (flag register, program counter),
// this class ends up being a little messy.
class RegisterFile : public Memory<uint8_t, REG_FILE_SIZE>
{
private:
    void SetFlag(FlagAddr addr);
public:
    void Write(size_t addr, uint8_t data) override;
    void Clear() override;
    void UpdateFlags(uint16_t data, uint8_t input_a, uint8_t input_b);
    void ClearFlags();
    bool TestFlag(FlagAddr addr) const;

#ifndef NDEBUG
    void Print(std::ostream& os);
#endif
};

#endif //SOFTCPU2_REGISTERFILE_HPP