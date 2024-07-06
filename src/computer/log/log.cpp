//
// Created by Aubrey on 6/22/2024.
//

#include "log.hpp"

void format_log(std::ostream& log)
{
    log << std::left << std::setw(4) << std::setfill(' ');
}

void print_header(std::ostream& log)
{
    std::string header[] = {"Cyc  ", "Op", "A", "B", "Registers"};

    for (const std::string& str : header)
    {
        format_log(log);
        log << str.c_str();
    }
    log << std::endl;
}

void print_op(std::ostream& log, uint8_t op)
{
    std::string str_op;

    switch (op)
    {
        case HLT:
            str_op = "HLT";
            break;

        case JIN:
            str_op = "JIN";
            break;

        case CMP:
            str_op = "CMP";
            break;

        case ADD:
            str_op = "ADD";
            break;

        case SUB:
            str_op = "SUB";
            break;

        case AND:
            str_op = "AND";
            break;

        case ORR:
            str_op = "ORR";
            break;

        case XOR:
            str_op = "XOR";
            break;

        case LSH:
            str_op = "LSH";
            break;

        case RSH:
            str_op = "RSH";
            break;

        case INC:
            str_op = "INC";
            break;

        case DEC:
            str_op = "DEC";
            break;

        case LOD:
            str_op = "LOD";
            break;

        case LDI:
            str_op = "LDI";
            break;

        case STO:
            str_op = "STO";
            break;

        case CPR:
            str_op = "CPR";
            break;

        default:
            str_op = "UHOHHHHHHH";
            break;
    }
    format_log(log);
    log << str_op;
}