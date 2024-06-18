//
// Created by Aubrey on 6/16/2024.
//

#include "CPU.hpp"

uint16_t CPU::Fetch(uint8_t PC)
{
    return prog_mem.Read(PC);
}

void CPU::DecodeAndExecute(uint16_t instr)
{

}

void CPU::WriteBack()
{

}

void CPU::UpdateFlags()
{

}

void CPU::Run(int64_t num_cycles)
{
    if (num_cycles < 0)
    {
        while (!halt)
        {
            Step();
        }
    }
    else
    {
        for (size_t i = 0; !halt && i < num_cycles; i++)
        {
            Step();
        }
    }
}

void CPU::Step()
{
    // TODO: Fetch, execute, writeback etc
    uint16_t instruction = Fetch(reg_file.Read(PROG_CNTR_ADDR));
    DecodeAndExecute(instruction);
    cycles++;
}

void CPU::Reset()
{
    reg_file.Write(PROG_CNTR_ADDR, 0);

}

void CPU::Halt()
{
    halt = true;
}

void CPU::LoadProgram(std::ifstream &input_file)
{
    prog_mem.Clear();
    uint8_t byte1, byte2;

    // Read two bytes at a time until read address is 256
    while (input_file.read(reinterpret_cast<char*>(&byte1), 1) && input_file.read(reinterpret_cast<char*>(&byte2), 1))
    {
        // Construct instruction word (little endian)
        uint16_t instr_word = (uint16_t(byte2) << 8) | byte1;

        prog_mem.Write(input_file.tellg(), instr_word);

        // Check if read address is 256 or higher
        if (input_file.tellg() >= 256)
        {
            break;
        }
    }
}