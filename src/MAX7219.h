#ifndef MAX7219_MAX7219_H
#define MAX7219_MAX7219_H

#include "stm32f1xx_hal.h"
#include "MAX7219_Register.h"
#include "MAX7219_Pin.h"

class MAX7219 {

    // TODO add picture of the SPI configuration
    SPI_HandleTypeDef &spi;
    MAX7219_Pin cs;

    void sendPacket(uint16_t packet);
    void sendPacket(MAX7219_Register reg, uint8_t value);

public:

    MAX7219(SPI_HandleTypeDef &spi, MAX7219_Pin cs);

    void shutdown(bool value);
    void intensity(uint8_t value);
    void sendDigit(uint8_t digit, uint8_t data);
    void scanLimit(uint8_t limit);

};


#endif //MAX7219_MAX7219_H
