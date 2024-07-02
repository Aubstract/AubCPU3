//
// Created by Aubrey on 6/22/2024.
//

#ifndef SOFTCPU2_LOG_CPP
#define SOFTCPU2_LOG_CPP

#include "../CPU/Opcode.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

void format_log(std::ostream& log);
void print_header(std::ostream& log);
void print_op(std::ostream& log, uint8_t op);

#endif // SOFTCPU2_LOG_CPP