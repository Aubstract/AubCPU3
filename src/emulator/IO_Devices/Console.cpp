//
// Created by Aubrey on 6/22/2024.
//

#include "Console.hpp"

uint8_t Console::GetInput()
{
    uint8_t input_buff;
    this->istrm >> input_buff;
    return input_buff;
}

void Console::Output(uint8_t data)
{
    switch (this->mode)
    {
        case UINT:
            this->ostrm << static_cast<unsigned int>(data);
            break;
        case CHAR:
            this->ostrm << static_cast<char>(data);
            break;
    }
    this->ostrm  << std::flush;
}

void Console::SetMode(ConsoleMode new_mode)
{
    this->mode = new_mode;
}

