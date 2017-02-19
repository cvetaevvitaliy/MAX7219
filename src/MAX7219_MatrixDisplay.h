#ifndef MAX7219_MAX7219_MATRIXDISPLAY_H
#define MAX7219_MAX7219_MATRIXDISPLAY_H

#include "MAX7219.h"
#include <array>

template<std::size_t X, std::size_t Y>
class MAX7219_MatrixDisplay {

    MAX7219<X * Y> &max;

    typedef std::array<uint8_t, X * Y> DigitData;
    std::array<DigitData, 8> buffer;

    uint8_t &getByte(uint8_t x, uint8_t y) {
        int digit = y % 8;
        int row = y / 8;
        int col = x / 8;
        int bytePos = col + row * X;
        return buffer[digit][bytePos];
    }

public:

    MAX7219_MatrixDisplay(MAX7219<X * Y> &max)
            : max(max) {
    }

    void writePixel(uint8_t x, uint8_t y, bool value) {
        if (value) {
            getByte(x, y) |= 1 << (x % 8);
        } else {
            getByte(x, y) &= ~(1 << (x % 8));
        }
    }

    bool getPixel(uint8_t x, uint8_t y) {
        return static_cast<bool>(getByte(x, y) & (1 << (x % 8)));
    }

    void write() {
        for (uint8_t i = 0; i < 8; i++) {
            max.sendDigit(i, buffer[i]);
        }
    }

};


#endif //MAX7219_MAX7219_MATRIXDISPLAY_H
