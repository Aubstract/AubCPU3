//
// Created by Aubrey on 6/16/2024.
//

#ifndef SOFTCPU2_CPU_HPP
#define SOFTCPU2_CPU_HPP

#ifndef NDEBUG
    #include "../log/log.hpp"
#endif

#include "ALU.hpp"
#include "Memory.hpp"
#include "../IO_Devices/IOManager.hpp"
#include "RegisterFile.hpp"
#include "Opcode.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

constexpr size_t PROG_MEM_SIZE = 256;

// This class represents the entire CPU.
// It is composed of a number of other classes, each representing a piece of the CPU.
// It exposes functions like Run and Step that allow the user to run a program on it.
class CPU
{
private:
    std::ofstream& log;
    RegisterFile reg_file;
    IOManager io_mem;
    Memory<uint16_t, PROG_MEM_SIZE> prog_mem;

    uint64_t cycles = 0;
    bool halt = true;

    uint16_t Fetch(uint8_t PC);
    void DecodeAndExecute(uint16_t instr);

public:
    CPU(std::ofstream& log_file,
        std::ostream& console_out,
        std::istream& console_in);
    void Run(int64_t num_cycles);
    void Step();
    void ResetMemory();
    void Halt();
    void LoadProgram(std::ifstream&);
};

#endif //SOFTCPU2_CPU_HPP