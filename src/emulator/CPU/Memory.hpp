//
// Created by Aubrey on 6/17/2024.
//

#ifndef SOFTCPU2_MEMORY_HPP
#define SOFTCPU2_MEMORY_HPP

//#include "Register.hpp"
#include <array>
#include <cstdint>
#ifndef NDEBUG
    #include <stdexcept>
#endif

template<typename T, size_t N>
class Memory
{
protected:
    std::array<T, N> registers;
public:
    virtual T Read(size_t addr) const
    {
#ifndef NDEBUG
        if (addr >= registers.size())
        {
            throw std::out_of_range("Index out of range in Memory.Read()");
        }
#endif
        return registers[addr];
    }

    virtual void Write(size_t addr, T data)
    {
#ifndef NDEBUG
        if (addr >= registers.size())
        {
            throw std::out_of_range("Index out of range in Memory.Write()");
        }
#endif
        registers[addr] = data;
    }

    virtual void Clear()
    {
        for (size_t i = 0; i < registers.size(); i++)
        {
            this->Write(i, 0);
        }
    }
};

#endif //SOFTCPU2_MEMORY_HPP
