/*!
 * @file Adafruit_STTC4.h
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
 * Written by Limor 'ladyada' Fried with assistance from Claude Code
 * for Adafruit Industries.
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */

#ifndef _ADAFRUIT_STTC4_H
#define _ADAFRUIT_STTC4_H

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Arduino.h>
#include <Wire.h>

/** Default I2C address for the STTC4 */
#define STTC4_DEFAULT_ADDR 0x64

/** Command: Start continuous measurement */
#define STTC4_CMD_START_CONTINUOUS_MEASUREMENT 0x218B
/** Command: Stop continuous measurement */
#define STTC4_CMD_STOP_CONTINUOUS_MEASUREMENT 0x3F86
/** Command: Read measurement */
#define STTC4_CMD_READ_MEASUREMENT 0xEC05
/** Command: Set RHT compensation */
#define STTC4_CMD_SET_RHT_COMPENSATION 0xE000
/** Command: Set pressure compensation */
#define STTC4_CMD_SET_PRESSURE_COMPENSATION 0xE016
/** Command: Measure single shot */
#define STTC4_CMD_MEASURE_SINGLE_SHOT 0x219D
/** Command: Enter sleep mode */
#define STTC4_CMD_ENTER_SLEEP_MODE 0x3650
/** Command: Exit sleep mode payload byte */
#define STTC4_CMD_EXIT_SLEEP_MODE 0x00
/** Command: Perform conditioning */
#define STTC4_CMD_PERFORM_CONDITIONING 0x29BC
/** Command: Perform soft reset */
#define STTC4_CMD_PERFORM_SOFT_RESET 0x06
/** Command: Perform factory reset */
#define STTC4_CMD_PERFORM_FACTORY_RESET 0x3632
/** Command: Perform self test */
#define STTC4_CMD_PERFORM_SELF_TEST 0x278C
/** Command: Enable testing mode */
#define STTC4_CMD_ENABLE_TESTING_MODE 0x3FBC
/** Command: Disable testing mode */
#define STTC4_CMD_DISABLE_TESTING_MODE 0x3F3D
/** Command: Perform forced recalibration */
#define STTC4_CMD_PERFORM_FORCED_RECALIBRATION 0x362F
/** Command: Get product ID */
#define STTC4_CMD_GET_PRODUCT_ID 0x365B

/** Expected product ID */
#define STTC4_PRODUCT_ID 0x0901018A

/*!
 * @brief Class that stores state and functions for interacting with
 * the STTC4 CO2 sensor
 */
class Adafruit_STTC4 {
 public:
  Adafruit_STTC4();
  ~Adafruit_STTC4();

  bool begin(uint8_t i2c_addr = STTC4_DEFAULT_ADDR, TwoWire* wire = &Wire);

 private:
  Adafruit_I2CDevice* i2c_dev;
  uint8_t crc8(const uint8_t* data, uint8_t len);
};

#endif // _ADAFRUIT_STTC4_H
