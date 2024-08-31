//
// Created by Aubrey on 6/20/2024.
//

#include "AddrSpaceManager.hpp"

constexpr size_t CONSOLE_OPCODE_ADDR = 2;
constexpr size_t CONSOLE_OUT_ADDR = 3;
constexpr size_t CONSOLE_IN_ADDR = 8;

uint8_t AddrSpaceManager::Read(size_t addr)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr == CONSOLE_IN_ADDR)
        {
            // TODO: Find a better way to deal with "internal" addresses for each device
            return console.Read(2); // Address of console read register (basically std::cin)
        }
        else
        {
            throw std::out_of_range("Invalid read address in AddrSpaceManager::Read()");
        }
    }
    return data_mem.Read(addr - IO_ADDR_SPACE_SIZE);
}

void AddrSpaceManager::Write(size_t addr, uint8_t data)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr == CONSOLE_OPCODE_ADDR)
        {
            console.Write(1, data);
        }
        else if (addr == CONSOLE_OUT_ADDR)
        {
            console.Write(0, data);
        }
        else
        {
            throw std::out_of_range("Invalid write address in AddrSpaceManager::Write()");
        }
    }
    else
    {
        data_mem.Write(addr - IO_ADDR_SPACE_SIZE, data);
    }
}

void AddrSpaceManager::ClearMem()
{
    console.Clear();
    data_mem.Clear();
}