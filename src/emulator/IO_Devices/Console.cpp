//
// Created by Aubrey on 6/22/2024.
//

#include "Console.hpp"

uint8_t Console::GetInput()
{
    uint8_t input_buff;
    istrm >> input_buff;
    return input_buff;

    /*
    uint8_t uint_buff;
    char char_buff;

    switch (this->mode)
    {
        case UINT:

            break;
        case CHAR:
            istrm >> char_buff;
            input_mem.Write(addr, static_cast<uint8_t>(char_buff));
            break;
    }
     */
}

void Console::Output(uint8_t data) {
    switch (this->mode)
    {
        case UINT:
            ostrm << (unsigned int)(data);
            break;
        case CHAR:
            ostrm << char(data);
            break;
    }
    ostrm  << std::flush;
}

void Console::SetMode(ConsoleMode new_mode)
{
    this->mode = new_mode;
}

