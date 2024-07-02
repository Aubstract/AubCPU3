//
// Created by Aubrey on 6/19/2024.
//

#ifndef SOFTCPU2_IODEVICE_HPP
#define SOFTCPU2_IODEVICE_HPP

#include "../CPU/Memory.hpp"
#include <cstdint>

template <size_t NUM_INPUT, size_t NUM_OUTPUT>
class IODevice
{
protected:
    uint8_t base_addr;
    size_t addr_space_size;
    Memory<uint8_t, NUM_INPUT> input_mem;
    Memory<uint8_t, NUM_OUTPUT> output_mem;
    virtual void ReadActive(size_t addr) = 0;
    virtual void WriteActive(size_t addr) = 0;

public:
    IODevice(uint8_t base_addr) : base_addr(base_addr),
                                  addr_space_size(NUM_INPUT + NUM_OUTPUT) {};

    void Write(size_t addr, uint8_t data)
    {
        output_mem.Write(addr, data);
        WriteActive(addr);
    }

    uint8_t Read(size_t addr)
    {
        ReadActive(addr - NUM_OUTPUT);
        return input_mem.Read(addr - NUM_OUTPUT);
    }

    void Clear()
    {
        input_mem.Clear();
        output_mem.Clear();
    }
};

#endif //SOFTCPU2_IODEVICE_HPP
