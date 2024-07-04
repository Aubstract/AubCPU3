#include "CPU/CPU.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ofstream log("../src/computer/log/log.txt");

    CPU cpu(log, std::cout, std::cin);

    std::string path;
    std::cout << "Enter the file path to the binary file: " << std::flush;
    std::cin >> path;

    std::ifstream bin(path, std::ios::binary | std::ios::in);
    assert(bin);

    cpu.LoadProgram(bin);
    cpu.Run(-1);

    return 0;
}
