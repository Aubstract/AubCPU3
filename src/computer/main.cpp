//#define NDEBUG

#include <cassert>
#include <fstream>
#include "CPU/CPU.hpp"

int main() {
    CPU cpu;
    std::ifstream fib_bin("../src/assembler/bin_files/fib.bin", std::ios::binary | std::ios::in);

    assert(fib_bin);

    cpu.LoadProgram(fib_bin);
    cpu.Run(-1);

    return 0;
}
