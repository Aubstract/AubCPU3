#include "CPU/CPU.hpp"
#include <cassert>
#include <iostream>
#include <string>

int main()
{
    std::ofstream log("../src/computer/log.txt");
    assert(log);
    CPU cpu(log, std::cout, std::cin);
    std::string path;

    std::cout << "Enter the file path to the binary file: " << std::flush;
    std::cin >> path;

    std::ifstream fib_bin(path, std::ios::binary | std::ios::in);
    assert(fib_bin);

    cpu.LoadProgram(fib_bin);
    cpu.Run(4000);

    return 0;
}
