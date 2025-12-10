/*!
 * @file Adafruit_STTC4.cpp
 *
 * @mainpage Adafruit STTC4 CO2 sensor driver
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's STTC4 driver for the
 * Arduino platform. It is designed specifically to work with the
 * Adafruit STTC4 breakout: https://www.adafruit.com/product/xxxx
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor 'ladyada' Fried with assistance from Claude Code
 * for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */

#include "Adafruit_STTC4.h"

/*!
 * @brief Instantiates a new STTC4 class
 */
Adafruit_STTC4::Adafruit_STTC4() {
  i2c_dev = nullptr;
}

/*!
 * @brief Destructor for STTC4 class
 */
Adafruit_STTC4::~Adafruit_STTC4() {
  if (i2c_dev) {
    delete i2c_dev;
  }
}

/*!
 * @brief Initializes the STTC4 sensor
 * @param i2c_addr The I2C address of the sensor (default 0x64)
 * @param wire The Wire object to use for I2C communication (default &Wire)
 * @return true if initialization was successful, false otherwise
 */
bool Adafruit_STTC4::begin(uint8_t i2c_addr, TwoWire* wire) {
  if (i2c_dev) {
    delete i2c_dev;
  }

  i2c_dev = new Adafruit_I2CDevice(i2c_addr, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  // Verify product ID
  uint8_t cmd[2] = {(uint8_t)(STTC4_CMD_GET_PRODUCT_ID >> 8),
                    (uint8_t)(STTC4_CMD_GET_PRODUCT_ID & 0xFF)};
  uint8_t data[18]; // 6 x (2 bytes + 1 CRC)

  if (!i2c_dev->write_then_read(cmd, 2, data, 18, true)) {
    return false;
  }

  // Verify CRC for first two data words (product ID)
  if (crc8(&data[0], 2) != data[2]) {
    return false; // CRC mismatch for first word
  }
  if (crc8(&data[3], 2) != data[5]) {
    return false; // CRC mismatch for second word
  }

  // Extract product ID from first 4 bytes (MSB first, with CRCs at bytes 2, 5)
  uint32_t product_id = ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) |
                        ((uint32_t)data[3] << 8) | data[4];

  if (product_id != STTC4_PRODUCT_ID) {
    return false;
  }

  return true;
}

/*!
 * @brief Calculate CRC-8 checksum for STTC4 data
 * @param data Pointer to data bytes
 * @param len Number of bytes to calculate CRC for
 * @return CRC-8 checksum
 */
uint8_t Adafruit_STTC4::crc8(const uint8_t* data, uint8_t len) {
  uint8_t crc = 0xFF;
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (uint8_t bit = 8; bit > 0; --bit) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x31;
      } else {
        crc = (crc << 1);
      }
    }
  }
  return crc;
}
