#include "MAX7219.h"
#include "MAX7219_MatrixDisplay.h"

extern SPI_HandleTypeDef hspi1;

extern "C" void example() {

    MAX7219 max(hspi1, {GPIOA, GPIO_PIN_4});
    MAX7219_MatrixDisplay display(max);

    max.shutdown(false);
    max.intensity(5);
    max.scanLimit(7);

    int count = 0;

    while (true) {

        // Example of using MAX7219 directly
//        max.sendDigit(0, 0xAA);
//        max.sendDigit(2, 0xAA);
//        max.sendDigit(4, 0xAA);
//        max.sendDigit(6, 0xAA);
//
//        max.sendDigit(1, 0x55);
//        max.sendDigit(3, 0x55);
//        max.sendDigit(5, 0x55);
//        max.sendDigit(7, 0x55);

        // Example using MAX7219_MatrixDisplay
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                display.writePixel(x, y, x + y == count);
            }
        }
        display.write();
        count++;
        count &= 0x0F;

        HAL_Delay(50);
    }

}