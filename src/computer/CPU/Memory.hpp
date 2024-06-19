//
// Created by Aubrey on 6/17/2024.
//

#ifndef SOFTCPU2_MEMORY_HPP
#define SOFTCPU2_MEMORY_HPP

#include "Register.hpp"
#include <array>
#include <cstdint>

template<typename T, size_t N>
class Memory
{
protected:
    std::array<Register<T>, N> registers;
public:
    virtual T Read(size_t addr) const
    {
        return registers.at(addr).read();
    }

    virtual void Write(size_t addr, T data)
    {
        registers.at(addr).write(data);
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
