#include "CPU/CPU.hpp"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::ofstream log("../src/computer/log/log_files/log.txt");
    assert(log);

    CPU cpu(log, std::cout, std::cin);

    std::string path;
    std::cout << "Enter the file path to the binary file: " << std::flush;
    std::cin >> path;

    std::ifstream bin(path, std::ios::binary | std::ios::in);
    assert(bin);

    cpu.LoadProgram(bin);

    // Time the execution
    auto start = std::chrono::high_resolution_clock::now();

    cpu.Run(-1);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\n\n Microseconds:\n" << duration.count() << std::endl;

    return 0;
}
