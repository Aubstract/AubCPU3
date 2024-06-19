//
// Created by Aubrey on 6/16/2024.
//

#ifndef SOFTCPU2_CPU_HPP
#define SOFTCPU2_CPU_HPP

#include "ALU.hpp"
#include "Memory.hpp"
#include "RegisterFile.hpp"
#include "Opcode.hpp"
#include <cassert>
#include <fstream>
#include <vector>

inline constexpr size_t DATA_MEM_SIZE = 256;
inline constexpr size_t PROG_MEM_SIZE = 256;

class CPU
{
private:
    RegisterFile reg_file;
    Memory<uint8_t, DATA_MEM_SIZE> data_mem;
    Memory<uint16_t, PROG_MEM_SIZE> prog_mem;

    uint64_t cycles = 0;
    bool halt = true;

    uint16_t Fetch(uint8_t PC);
    void DecodeAndExecute(uint16_t instr);

public:
    void Run(int64_t num_cycles);
    void Step();
    void ResetMemory();
    void Halt();
    void LoadProgram(std::ifstream&);
};

#endif //SOFTCPU2_CPU_HPP