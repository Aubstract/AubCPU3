//
// Created by Aubrey on 6/16/2024.
//

#include "CPU.hpp"

inline constexpr uint16_t OPCODE_BITMASK = 0x000F;
inline constexpr uint16_t ARG_A_BITMASK = 0x00F0;
inline constexpr uint16_t ARG_B_BITMASK = 0x0F00;
inline constexpr uint16_t UPPER_BYTE_BITMASK = 0xFF00;

CPU::CPU(std::ofstream& log_file,
         std::ostream& console_out,
         std::istream& console_in)
         : log(log_file),
           io_mem(console_out, console_in)

{}

uint16_t CPU::Fetch(uint8_t PC)
{
    return prog_mem.Read(PC);
}

void decode_pattern_a(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Src1/Dest)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);

    // Extract and push argument B (Src2)
    temp_arg = (instr & ARG_B_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void decode_pattern_b(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Dest)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);

    // Extract and push argument B (Ptr)
    temp_arg = (instr & ARG_B_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void decode_pattern_c(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Src)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);

    // Extract and push argument B (Ptr)
    temp_arg = (instr & ARG_B_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void decode_pattern_d(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Src/Dest)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);
}

void decode_pattern_e(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Dest)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);

    // Extract and push argument B (Src)
    temp_arg = (instr & ARG_B_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void decode_pattern_f(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Dest)
    uint8_t temp_arg = (instr & ARG_A_BITMASK) >> 4;
    args.push_back(temp_arg);

    // Extract and push argument B (Immediate Value)
    temp_arg = (instr & UPPER_BYTE_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void decode_pattern_g(std::vector<uint8_t>& args, uint16_t instr)
{
    // Extract and push argument A (Instruction Address)
    uint8_t temp_arg = (instr & UPPER_BYTE_BITMASK) >> 8;
    args.push_back(temp_arg);
}

void CPU::DecodeAndExecute(uint16_t instr)
{
    uint8_t opcode = instr & OPCODE_BITMASK;
#ifndef NDEBUG
    print_op(log, opcode);
#endif

    std::vector<uint8_t> args;

    uint8_t alu_in_a,
            alu_in_b;
    uint16_t alu_out;

    switch (opcode)
    {
        case HLT:
            Halt();
            // No decode
            // No write back
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case JIN:
            // Decode
            decode_pattern_g(args, instr);
            // Execute
            if (reg_file.TestFlag(not_zero))
            {
                reg_file.Write(PROG_CNTR_ADDR, args.at(0));
            }
            else
            {
                // Increment PC
                reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            }
            // No write back apart from updating the PC during execute phase
            // Don't update flags
            // Don't increment PC again
            break;

        case CMP:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(SUB, alu_in_a, alu_in_b);
            // No write back
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case ADD:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(ADD, alu_in_a, alu_in_b);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case SUB:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(SUB, alu_in_a, alu_in_b);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case AND:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(AND, alu_in_a, alu_in_b);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case ORR:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(ORR, alu_in_a, alu_in_b);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case XOR:
            // Decode
            decode_pattern_a(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_in_b = reg_file.Read(args.at(1));
            alu_out = ALU::Operate(XOR, alu_in_a, alu_in_b);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case LSH:
            // Decode
            decode_pattern_d(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_out = ALU::Operate(LSH, alu_in_a, 0);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case RSH:
            // Decode
            decode_pattern_d(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_out = ALU::Operate(RSH, alu_in_a, 0);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Update flags
            reg_file.UpdateFlags(alu_out, args.at(0), args.at(1));
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case INC:
            // Decode
            decode_pattern_d(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_out = ALU::Operate(INC, alu_in_a, 0);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case DEC:
            // Decode
            decode_pattern_d(args, instr);
            // Execute
            alu_in_a = reg_file.Read(args.at(0));
            alu_out = ALU::Operate(DEC, alu_in_a, 0);
            // Write back
            reg_file.Write(args.at(0), alu_out);
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case LOD:
            // Decode
            decode_pattern_b(args, instr);
            // No execute
            // Write back
            reg_file.Write(args.at(0), io_mem.Read(reg_file.Read(args.at(1))));
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case LDI:
            // Decode
            decode_pattern_f(args, instr);
            // No execute
            // Write back
            reg_file.Write(args.at(0), args.at(1));
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case STO:
            // Decode
            decode_pattern_c(args, instr);
            // No execute
            // Write back
            io_mem.Write(reg_file.Read(args.at(1)), reg_file.Read(args.at(0)));
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        case CPR:
            // Decode
            decode_pattern_e(args, instr);
            // No execute
            // Write back
            reg_file.Write(args.at(0), reg_file.Read(args.at(1)));
            // Don't update flags
            // Increment PC
            reg_file.Write(PROG_CNTR_ADDR, reg_file.Read(PROG_CNTR_ADDR) + 1);
            break;

        default:
            // Should never reach this since the opcode can only be in [0, 15]
#ifndef NDEBUG
            assert(false); // Opcode is invalid somehow
#endif
            break;
    }
#ifndef NDEBUG
    for (size_t i = 0; i < 2; i++)
    {
        format_log(log);
        if (i < args.size())
        {
            log << int(args.at(i));
        }
        else
        {
            log << " ";
        }
    }
#endif
}

void CPU::Run(int64_t num_cycles)
{
    if (num_cycles == 0)
    {
        return;
    }

    halt = false;

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
    uint16_t instruction = Fetch(reg_file.Read(PROG_CNTR_ADDR));
#ifndef NDEBUG
    if (cycles % 50 == 0)
    {
        print_header(log);
    }
    format_log(log);
    log << int(cycles + 1);
#endif
    DecodeAndExecute(instruction);
    cycles++;
#ifndef NDEBUG
    reg_file.Print(log);
    log << std::endl;
#endif
}

void CPU::ResetMemory()
{
    reg_file.Clear();
    io_mem.ClearMem();
    prog_mem.Clear();
}

void CPU::Halt()
{
    halt = true;
}

void CPU::LoadProgram(std::ifstream& input_file)
{
    ResetMemory();
    uint8_t byte1, byte2;

    // char* byte1_ptr = &byte1;
    // char* byte2_ptr = &byte2;

    // Read two bytes at a time until read address is 256
    while (input_file.read(reinterpret_cast<char*>(&byte1), 1) && input_file.read(reinterpret_cast<char*>(&byte2), 1))
    {
        // Construct instruction word (little endian)
        uint16_t instr_word = (uint16_t(byte2) << 8) | byte1;
        size_t write_addr = (int(input_file.tellg()) / 2) - 1;

        prog_mem.Write(write_addr, instr_word);

        // Check if read address is greater than the size of the CPU's program memory
        if (input_file.tellg() >= (PROG_MEM_SIZE * 2))
        {
            break;
        }
    }
}