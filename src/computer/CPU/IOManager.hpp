//
// Created by Aubrey on 6/20/2024.
//

#ifndef SOFTCPU2_IOMANAGER_HPP
#define SOFTCPU2_IOMANAGER_HPP

#include "../IO_Devices/ConsoleDevice.hpp"
#include "Memory.hpp"
#include <cstdint>
#include <iostream>

constexpr size_t DATA_MEM_SIZE = 256;
constexpr size_t IO_ADDR_SPACE_SIZE = 16;

class IOManager
{
private:
    Memory<uint8_t, DATA_MEM_SIZE - IO_ADDR_SPACE_SIZE> data_mem;
    ConsoleDevice console;
public:
    IOManager();
    uint8_t Read(size_t addr);
    void Write(size_t addr, uint8_t data);
    void ClearMem();
};

#endif //SOFTCPU2_IOMANAGER_HPP
