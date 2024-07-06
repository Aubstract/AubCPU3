//
// Created by Aubrey on 6/13/2024.
//

#include "RegisterFile.hpp"

void RegisterFile::Write(size_t addr, uint8_t data)
{
    if (addr != HARDWIRE_ZERO_ADDR)
    {
#ifndef NDEBUG
        if (addr >= registers.size())
        {
            throw std::out_of_range("Index out of range in RegisterFile.Write()");
        }
#endif
        this->registers[addr] = data;
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
#ifndef NDEBUG
    assert(FLAG_REG_ADDR < registers.size());
#endif
    this->registers[FLAG_REG_ADDR] = 0;
}

bool RegisterFile::TestFlag(FlagAddr addr) const
{
#ifndef NDEBUG
    assert(FLAG_REG_ADDR < registers.size());
#endif
    return this->registers[FLAG_REG_ADDR] & (uint8_t(1) << addr);
}

void RegisterFile::SetFlag(FlagAddr addr)
{
#ifndef NDEBUG
    assert(addr <= FLAG_ADDR_MAX);
    assert(FLAG_REG_ADDR < registers.size());
#endif
    this->registers[FLAG_REG_ADDR] = this->registers[FLAG_REG_ADDR] | (uint8_t(1) << addr);
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
