#ifndef MAX7219_MAX7219_H
#define MAX7219_MAX7219_H

#include <array>
#include "stm32f1xx_hal.h"
#include "MAX7219_Register.h"
#include "MAX7219_Pin.h"

template<std::size_t N>
class MAX7219 {

    // TODO add picture of the SPI configuration
    SPI_HandleTypeDef &spi;
    MAX7219_Pin cs;

    void sendPackets(const std::array<uint16_t, N> &packets) {
        cs.low();
        HAL_SPI_Transmit(&spi, reinterpret_cast<uint8_t *>(const_cast<uint16_t *>(packets.data())), N, 100);
        cs.high();
    }

    void sendPacket(MAX7219_Register reg, uint8_t value) {
        std::array<uint16_t, N> packets;
        for (uint16_t &v : packets) {
            v = makePacket(reg, value);
        }
        sendPackets(packets);
    }

    uint16_t makePacket(MAX7219_Register reg, uint8_t value) {
        return (static_cast<uint8_t >(reg) << 8) | value;
    }

public:

    MAX7219(SPI_HandleTypeDef &spi, MAX7219_Pin cs)
            : spi(spi), cs(cs) {
    }

    void shutdown(bool value) {
        if (value) {
            sendPacket(MAX7219_Register::Shutdown, 0);
        } else {
            sendPacket(MAX7219_Register::Shutdown, 1);
        }
    }

    void intensity(uint8_t value) {
        sendPacket(MAX7219_Register::Intensity, value & 0x0F);
    }

    void sendDigit(uint8_t digit, const std::array<uint8_t, N> &data) {
        digit &= 0x07;
        std::array<uint16_t, N> packets;
        for (std::size_t i = 0; i < N; i++) {
            packets[i] = makePacket(MAX7219_Register(static_cast<uint8_t>(MAX7219_Register::Digit0) + digit), data[i]);
        }
        sendPackets(packets);
    }

    void scanLimit(uint8_t limit) {
        sendPacket(MAX7219_Register::ScanLimit, limit & 0x07);
    }

};


#endif //MAX7219_MAX7219_H
