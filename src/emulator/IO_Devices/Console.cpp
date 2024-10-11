//
// Created by Aubrey on 6/22/2024.
//

#include "Console.hpp"

constexpr char CLEAR_SCREEN = 18;

uint8_t Console::GetInput()
{
    int64_t input_buff;
    this->istrm >> input_buff;
    switch (this->mode)
    {
        case UINT:
            return static_cast<uint8_t>(input_buff);
            break;
        case CHAR:
            return static_cast<char>(input_buff);
            break;
    }
    return input_buff;
}

void Console::Output(uint8_t data)
{
    // Check for control char
    if (this->mode == CHAR && data == CLEAR_SCREEN)
    {
        this->ostrm << "\033[2J\033[H" << std::flush; // Clear screen and move cursor to (1,1)
        return; // early return
    }

    // Else if not a control char, print like normal
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

