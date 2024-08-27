//
// Created by Aubrey on 6/20/2024.
//

#include "IOManager.hpp"

constexpr size_t CONSOLE_OUT_ADDR = 0;
constexpr size_t CONSOLE_OPCODE_ADDR = 1;
constexpr size_t CONSOLE_IN_ADDR = 2;

uint8_t IOManager::Read(size_t addr)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr == CONSOLE_IN_ADDR)
        {
            return console.Read(addr);
        }
        else
        {
            throw std::out_of_range("Invalid read address in IOManager::Read()");
        }
    }
    return data_mem.Read(addr - IO_ADDR_SPACE_SIZE);
}

void IOManager::Write(size_t addr, uint8_t data)
{
    // Addressing an IO device
    if (addr < IO_ADDR_SPACE_SIZE)
    {
        if (addr == CONSOLE_OUT_ADDR || addr == CONSOLE_OPCODE_ADDR)
        {
            console.Write(addr, data);
        }
        else
        {
            throw std::out_of_range("Invalid write address in IOManager::Write()");
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