#include "MAX7219_MatrixDisplay.h"

MAX7219_MatrixDisplay::MAX7219_MatrixDisplay(MAX7219 &max)
        : max(max) {

}

void MAX7219_MatrixDisplay::writePixel(uint8_t x, uint8_t y, bool value) {
    if (value) {
        buffer[x] |= 1 << y;
    } else {
        buffer[x] &= ~(1 << y);
    }
}

bool MAX7219_MatrixDisplay::getPixel(uint8_t x, uint8_t y) {
    return static_cast<bool>(buffer[x] & (1 << y));
}

void MAX7219_MatrixDisplay::write() {
    for (uint8_t i = 0; i < 8; i++)
        max.sendDigit(i, buffer[i]);
}
