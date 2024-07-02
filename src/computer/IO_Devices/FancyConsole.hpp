//
// Created by Aubrey on 6/22/2024.
//

#ifndef SOFTCPU2_FANCYCONSOLE_HPP
#define SOFTCPU2_FANCYCONSOLE_HPP

#include "IODevice.hpp"
#include <iostream>

enum ConsoleOpcode
{
    UINT = 0,
    INT,
    CHAR
};

class FancyConsole : public IODevice<1, 2>
{
private:
    ConsoleOpcode op;
    std::ostream& os;
    std::istream& is;
    void ReadActive(size_t addr) override;
    void WriteActive(size_t addr) override;
public:
    FancyConsole(uint8_t base_addr, std::ostream& console_out, std::istream& console_in) : IODevice(base_addr),
                                                                                           op(UINT),
                                                                                           os(console_out),
                                                                                           is(console_in) {};
};


#endif //SOFTCPU2_FANCYCONSOLE_HPP
