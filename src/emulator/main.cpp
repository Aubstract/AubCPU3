#include "CPU/CPU.hpp"
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <process.h>
#include <string>

int main()
{
#ifndef NDEBUG
    // Init the log file
    std::ofstream log("../src/emulator/log/log_files/log.txt");
    assert(log);
#endif

#ifndef NDEBUG
    CPU cpu(log, std::cout, std::cin);
#else
    CPU cpu(std::cout, std::cin);
#endif

    std::string path;
    std::cout << "Enter the file path to the binary file: " << std::flush;
    std::cin >> path;

    // Get the source file (binary)
    std::ifstream bin(path, std::ios::binary | std::ios::in);
    assert(bin);

    cpu.LoadProgram(bin);

    // Time the execution
    auto start = std::chrono::high_resolution_clock::now();

    // Run the CPU (-1 means indefinitely)
    cpu.Run(-1);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\n\n Microseconds:\n" << duration.count() << std::endl;

    // Hang at the end of the program
    // system("pause");

    return 0;
}
