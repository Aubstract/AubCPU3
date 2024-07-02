//
// Created by Aubrey on 6/19/2024.
//

#include "Console.hpp"

void Console::WriteActive(size_t addr)
{
    os << output_mem.Read(addr) << std::flush;
}

void Console::ReadActive(size_t addr)
{
    char buff;
    is >> buff;
    input_mem.Write(addr, uint8_t(buff));
}