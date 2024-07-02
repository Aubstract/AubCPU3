//
// Created by Aubrey on 6/19/2024.
//

#include "ConsoleDevice.hpp"

void ConsoleDevice::WriteActive(size_t addr)
{
    os << output_mem.Read(addr) << std::flush;
}

void ConsoleDevice::ReadActive(size_t addr)
{
    std::string buff;
    std::cin >> buff;
    uint8_t temp = buff.at(0);
    input_mem.Write(addr, temp);
}