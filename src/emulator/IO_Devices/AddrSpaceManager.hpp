//
// Created by Aubrey on 6/20/2024.
//

#ifndef SOFTCPU2_AddrSpaceManager_HPP
#define SOFTCPU2_AddrSpaceManager_HPP

#include "FancyConsole.hpp"
#include "../CPU/Memory.hpp"
#include <cstdint>
#include <iostream>

constexpr size_t ADDR_SPACE_SIZE = 256;
constexpr size_t IO_ADDR_SPACE_SIZE = 16;
constexpr size_t MEM_ADDR_SPACE_SIZE = ADDR_SPACE_SIZE - IO_ADDR_SPACE_SIZE;

// AddrSpaceManager is basically an interface for main memory as well as I/O, since they occupy the same address
// space. It basically contains the memory map for this address space, directing data to/from the correct device
class AddrSpaceManager
{
private:
    Memory<uint8_t, MEM_ADDR_SPACE_SIZE> data_mem;
    FancyConsole console;
public:
    AddrSpaceManager(std::ostream& out, std::istream& in) : console(out, in) {};
    uint8_t Read(size_t addr);
    void Write(size_t addr, uint8_t data);
    void ClearMem();
};

#endif //SOFTCPU2_AddrSpaceManager_HPP
