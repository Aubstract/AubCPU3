//#define NDEBUG

#include "CPU/CPU.hpp"
#include <cassert>
#include <fstream>
#include <string>

int main()
{
    CPU cpu;
    std::string path;

    std::cout << "Enter the file path to the binary file: " << std::flush;
    std::cin >> path;

    std::ifstream fib_bin(path, std::ios::binary | std::ios::in);
    assert(fib_bin);

    cpu.LoadProgram(fib_bin);
    cpu.Run(-1);

    return 0;
}
