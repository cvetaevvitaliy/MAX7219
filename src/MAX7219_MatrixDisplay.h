#ifndef MAX7219_MAX7219_MATRIXDISPLAY_H
#define MAX7219_MAX7219_MATRIXDISPLAY_H

#include "MAX7219.h"
#include <array>

class MAX7219_MatrixDisplay {

    MAX7219 &max;
    std::array<uint8_t, 8> buffer;

public:

    MAX7219_MatrixDisplay(MAX7219 &max);

    void writePixel(uint8_t x, uint8_t y, bool value);
    bool getPixel(uint8_t x, uint8_t y);
    void write();

};


#endif //MAX7219_MAX7219_MATRIXDISPLAY_H
