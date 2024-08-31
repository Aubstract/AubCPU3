//
// Created by Aubrey on 6/22/2024.
//

#ifndef SOFTCPU2_FANCYCONSOLE_HPP
#define SOFTCPU2_FANCYCONSOLE_HPP

#include <cstdint>
#include <iostream>

// Defines the possible modes for the device to be in
enum ConsoleMode
{
    UINT = 0,
    CHAR
};

// Fancy Console is the I/O device that interfaces the AubCPU3 with the console.
// The original version just accepted an ASCII code and printed the character, this one is slightly *fancier*.
// Thus, the name.
//
// It has a few modes, which will determine how the input data is interpreted. Either as an unsigned integer,
// a signed integer, or an ASCII character
class Console //: public IODevice<1, 2>
{
private:
    ConsoleMode mode = UINT; // Current device mode
    std::ostream& ostrm; // Output stream (usually std::cout)
    std::istream& istrm; // Input stream (usually std::cin)
public:
    Console(std::ostream& console_out, std::istream& console_in) : ostrm(console_out),
                                                                   istrm(console_in) {};
    uint8_t GetInput();
    void Output(uint8_t data);
    void SetMode(ConsoleMode new_mode);
};

#endif //SOFTCPU2_FANCYCONSOLE_HPP
