//
// Created by Aubrey on 6/22/2024.
//

#ifndef SOFTCPU2_FANCYCONSOLE_HPP
#define SOFTCPU2_FANCYCONSOLE_HPP

#include "IODevice.hpp"
#include <iostream>

// Defines the possible modes for the device to be in
enum ConsoleOpcode
{
    UINT = 0,
    INT,
    CHAR
};

// Fancy Console is the I/O device that interfaces the AubCPU3 with the console.
// The original version just accepted an ASCII code and printed the character, this one is slightly *fancier*.
// Thus, the name.
//
// It has a few modes, which will determine how the input data is interpreted. Either as an unsigned integer,
// a signed integer, or an ASCII character
class FancyConsole : public IODevice<1, 2>
{
private:
    ConsoleOpcode op; // Current device mode
    std::ostream& os; // Output stream (usually std::cout)
    std::istream& is; // Input stream (usually std::cin)
    void ReadActive(size_t addr) override;
    void WriteActive(size_t addr) override;
public:
    FancyConsole(std::ostream& console_out, std::istream& console_in) : op(UINT),
                                                                        os(console_out),
                                                                        is(console_in) {};
};


#endif //SOFTCPU2_FANCYCONSOLE_HPP
