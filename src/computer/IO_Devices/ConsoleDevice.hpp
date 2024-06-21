//
// Created by Aubrey on 6/19/2024.
//

#ifndef SOFTCPU2_CONSOLEDEVICE_HPP
#define SOFTCPU2_CONSOLEDEVICE_HPP

// #include "../CPU/Memory.hpp"
#include "IODevice.hpp"
#include <cstdint>
#include <iostream>
#include <string>

class ConsoleDevice : public IODevice<1, 1>
{
private:
    std::ostream& os;
    std::istream& is;
    void WriteActive(size_t addr) override;
    void ReadActive(size_t addr) override;
public:
    ConsoleDevice(uint8_t base_addr, std::ostream& console_out, std::istream& console_in) : IODevice(base_addr),
                                                                                            os(console_out),
                                                                                            is(console_in) {};
};


#endif //SOFTCPU2_CONSOLEDEVICE_HPP
