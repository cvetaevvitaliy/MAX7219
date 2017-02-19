#include "MAX7219.h"

MAX7219::MAX7219(SPI_HandleTypeDef &spi, MAX7219_Pin cs)
        : spi(spi), cs(cs) {
}

void MAX7219::sendPacket(uint16_t packet) {
    cs.low();
    HAL_SPI_Transmit(&spi, reinterpret_cast<uint8_t *>(&packet), 1, 100);
    cs.high();
}

void MAX7219::sendPacket(MAX7219_Register reg, uint8_t value) {
    sendPacket((static_cast<uint8_t >(reg) << 8) | value);
}

void MAX7219::shutdown(bool value) {
    if (value) {
        sendPacket(MAX7219_Register::Shutdown, 0);
    } else {
        sendPacket(MAX7219_Register::Shutdown, 1);
    }
}

void MAX7219::intensity(uint8_t value) {
    sendPacket(MAX7219_Register::Intensity, value & 0x0F);
}

void MAX7219::sendDigit(uint8_t digit, uint8_t data) {
    digit &= 0x07;
    sendPacket(MAX7219_Register(static_cast<uint8_t>(MAX7219_Register::Digit0) + digit), data);
}

void MAX7219::scanLimit(uint8_t limit) {
    sendPacket(MAX7219_Register::ScanLimit, limit & 0x07);
}
