//
// Created by Aubrey on 6/19/2024.
//

#ifndef SOFTCPU2_CONSOLE_HPP
#define SOFTCPU2_CONSOLE_HPP

// #include "../CPU/Memory.hpp"
#include "IODevice.hpp"
#include <cstdint>
#include <iostream>
#include <string>

class Console : public IODevice<1, 1>
{
private:
    std::ostream& os;
    std::istream& is;
    void WriteActive(size_t addr) override;
    void ReadActive(size_t addr) override;
public:
    Console(uint8_t base_addr, std::ostream& console_out, std::istream& console_in) : IODevice(base_addr),
                                                                                            os(console_out),
                                                                                            is(console_in) {};
};


#endif //SOFTCPU2_CONSOLE_HPP
