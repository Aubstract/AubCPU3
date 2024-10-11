//
// Created by Aubrey on 9/30/2024.
//

#ifndef AUBCPU3_PIXELDISPLAY_HPP
#define AUBCPU3_PIXELDISPLAY_HPP

#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

constexpr uint8_t HEIGHT = 32;
constexpr uint8_t WIDTH = 64;

class PixelDisplay
{
private:
    uint8_t x = 0;
    std::array<std::array<char, WIDTH + 1>, HEIGHT + 1> screen = {};
    std::ostream& ostrm; // Output stream (usually std::cout)

    void clear()
    {
        for (auto& row : screen) {
            row.fill(' ');  // Fill each row with spaces (off pixels)
            row[WIDTH] = '|';
        }
        screen[HEIGHT].fill('-');
    }

    void printBorder() const {
        // Move cursor to top-left corner
        ostrm << "\033[H";  // Home position (row 1, column 1)

        // Top border
        ostrm << "+";
        for (int i = 0; i < WIDTH; ++i) {
            ostrm << "-";
        }
        ostrm << "+\n";

        // Side borders with blank space in between
        for (int y = 0; y < HEIGHT; ++y) {
            // Move the cursor explicitly to ensure positioning is correct
            ostrm << "\033[" << (y + 2) << ";1H";  // Move to start of line y + 2 (account for top border)
            ostrm << "|";  // Print the line number and left border

            for (int _x = 0; _x < WIDTH; ++_x) {
                ostrm << " ";  // Print the empty space
            }
            ostrm << "|" << y;  // Print the right border
        }

        // Move to bottom of the display and print bottom border
        ostrm << "\033[" << (HEIGHT + 2) << ";1H";  // Move to the row for bottom border
        ostrm << "+";
        for (int i = 0; i < WIDTH; ++i) {
            ostrm << "-";
        }
        ostrm << "+\n";

        ostrm.flush();
    }

    /*
    // Print the static border around the display
    void printBorder() const {
        // Move cursor to top-left corner
        ostrm << "\033[H";

        // Top border
        ostrm << "+";
        for (int i = 0; i < WIDTH; ++i) {
            ostrm << "-";
        }
        ostrm << "+\n";

        // Side borders with blank space in between
        for (int y = 0; y < HEIGHT; ++y) {
            ostrm << y << "|";
            for (int _x = 0; _x < WIDTH; ++_x) {
                ostrm << " ";
            }
            ostrm << "|" << std::endl;
        }

        // Bottom border
        ostrm << "+";
        for (int i = 0; i < WIDTH; ++i) {
            ostrm << "-";
        }
        ostrm << "+\n";

        ostrm.flush();
    }
     */

    void saveCursor()
    {
        ostrm << "\033[s";
    }

    void returnCursor() const
    {
        ostrm << "\033[u";
    }

public:
    PixelDisplay(std::ostream& os) : ostrm(os)
    {
        printBorder();
        ostrm << "\033[" << (HEIGHT + 4) << ";1H";  // Move cursor bottom
    }

    void setX(uint8_t _x)
    {
#ifndef NDEBUG
        assert(_x < WIDTH);
#endif
        x = _x;
    }

    void setYAndPlot(uint8_t y)
    {
#ifndef NDEBUG
        assert(y < HEIGHT);
#endif
        saveCursor();
        // Move cursor to (y + 1, x + 1) (ANSI escape codes are 1-based)
        ostrm << "\033[" << (y + 1) << ";" << (x + 1) << "H";
        ostrm << '#'; // Print the pixel
        ostrm << std::flush;
        returnCursor();
    }
};

#endif //AUBCPU3_PIXELDISPLAY_HPP
