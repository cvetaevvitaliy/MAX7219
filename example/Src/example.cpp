#include "MAX7219.h"
#include "MAX7219_MatrixDisplay.h"

extern SPI_HandleTypeDef hspi1;

extern "C" void example() {

    MAX7219<2> max(hspi1, {GPIOA, GPIO_PIN_4});
    MAX7219_MatrixDisplay<2, 1> display(max);

    max.shutdown(false);
    max.intensity(5);
    max.scanLimit(7);

    int count = 0;

    while (true) {

        // Example using MAX7219_MatrixDisplay
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 16; x++) {
                display.writePixel(x, y, x + y == count);
            }
        }
        display.write();
        count++;
        count %= 24;

        HAL_Delay(50);
    }

}