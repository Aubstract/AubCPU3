//
// Created by Aubrey on 6/22/2024.
//

#include "FancyConsole.hpp"

constexpr uint8_t SIGN_BIT_MASK = uint8_t(1) << 7;

int signed_byte_to_int(uint8_t num)
{
    int return_num = num;

    if (num & SIGN_BIT_MASK)
    {
        // -(256 - num)
        return_num = ((UINT8_MAX + 1) - int(num)) * -1;
    }

    return return_num;
}

void FancyConsole::WriteActive(size_t addr)
{
    if (addr == 1)
    {
        this->op = static_cast<ConsoleOpcode>(output_mem.Read(addr));
        return;
    }

    switch (this->op)
    {
        case UINT:
            os << int(output_mem.Read(addr));
            break;
        case INT:
            os << signed_byte_to_int(output_mem.Read(addr));
            break;
        case CHAR:
            os << char(output_mem.Read(addr));
            break;
    }
    os  << std::flush;
}

void FancyConsole::ReadActive(size_t addr)
{
    unsigned int uint_buff;
    int int_buff;
    char char_buff;

    switch (this->op)
    {
        case UINT:
            is >> uint_buff;
            input_mem.Write(addr, static_cast<uint8_t>(uint_buff));
            break;
        case INT:
            is >> int_buff;
            input_mem.Write(addr, static_cast<uint8_t>(int_buff));
            break;
        case CHAR:
            is >> char_buff;
            input_mem.Write(addr, static_cast<uint8_t>(char_buff));
            break;
    }
}
