//
// Created by Aubrey on 6/13/2024.
//

#include "RegisterFile.hpp"

void RegisterFile::Write(size_t addr, uint8_t data)
{
    if (addr != HARDWIRE_ZERO_ADDR)
    {
        this->registers.at(addr).write(data);
    }
}

void RegisterFile::Clear()
{
    Memory::Clear();
}

void RegisterFile::UpdateFlags(uint16_t alu_out, uint8_t alu_in_a, uint8_t alu_in_b)
{
    this->ClearFlags();

    if (alu_out == 0)
    {
        SetFlag(zero);
    }
    else
    {
        SetFlag(not_zero);
    }

    if (alu_out >> 8)
    {
        SetFlag(carry_out);
    }

    // Mask for the highest (8th) bit
    uint8_t bit_mask = uint8_t(1) << 7;

    if (alu_out & bit_mask)
    {
        SetFlag(sign_bit);
    }

    // O_flag = (a & !out & !b) | (!a & out & b)
    // but really just the highest bit of each, thus the bitmask
    bool o_flag = ((alu_in_a & bit_mask) && !(alu_out & bit_mask) && !(alu_in_b & bit_mask)) || (!(alu_in_a & bit_mask) && (alu_out & bit_mask) && (alu_in_b & bit_mask));

    if (o_flag)
    {
        SetFlag(overflow);
    }

    if (this->TestFlag(overflow) != this->TestFlag(sign_bit))
    {
        SetFlag(signed_less_than);
    }
}

void RegisterFile::ClearFlags()
{
    this->registers.at(FLAG_REG_ADDR).write(0);
}

bool RegisterFile::TestFlag(FlagAddr addr) const
{
#ifndef NDEBUG
    assert(addr <= FLAG_ADDR_MAX);
#endif
    return this->registers.at(FLAG_REG_ADDR).read() & (uint8_t(1) << addr);
}

void RegisterFile::SetFlag(FlagAddr addr)
{
#ifndef NDEBUG
    assert(addr <= FLAG_ADDR_MAX);
#endif
    this->registers.at(FLAG_REG_ADDR).write(this->registers.at(FLAG_REG_ADDR).read() | (uint8_t(1) << addr));
}

#ifndef NDEBUG
void RegisterFile::Print(std::ostream &os)
{
    for (size_t i = 0; i < REG_FILE_SIZE; i++)
    {
        format_log(os);
        os << int(this->Read(i));
    }
}
#endif
