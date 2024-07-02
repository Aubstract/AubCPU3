//
// Created by Aubrey on 6/20/2024.
//

#include "IOManager.hpp"

constexpr size_t CONSOLE_BASE_ADDR = 0;


IOManager::IOManager(std::ostream& console_out, std::istream& console_in)
                     : console(CONSOLE_BASE_ADDR, console_out, console_in)
{}

uint8_t IOManager::Read(size_t addr)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr <= CONSOLE_BASE_ADDR + 2)
        {
            return console.Read(addr);
        }
    }

    return data_mem.Read(addr - IO_ADDR_SPACE_SIZE);
}

void IOManager::Write(size_t addr, uint8_t data)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr <= CONSOLE_BASE_ADDR + 1)
        {
            console.Write(addr, data);
        }
    }
    else
    {
        data_mem.Write(addr - IO_ADDR_SPACE_SIZE, data);
    }
}

void IOManager::ClearMem()
{
    console.Clear();
    data_mem.Clear();
}