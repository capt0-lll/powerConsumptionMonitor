/**
 * @file    Adafruit_I2CRegister.h
 * @brief   Subset of Adafruit BusIO's Adafruit_I2CRegister and
 *          Adafruit_I2CRegisterBits.
 */
#pragma once

#include "Adafruit_I2CDevice.h"

/**
 * @brief A multi-byte register on an I2C device (8-bit register address).
 */
class Adafruit_I2CRegister {
 public:
  /**
   * @brief Constructor.
   * @param dev       Device that owns the register.
   * @param reg       Register address.
   * @param width     Register width in bytes (1..4 for value access).
   * @param byteorder MSBFIRST or LSBFIRST.
   */
  Adafruit_I2CRegister(Adafruit_I2CDevice* dev, uint16_t reg, uint8_t width,
                       uint8_t byteorder);

  /**
   * @brief  Read raw bytes from the register.
   * @param  buffer Destination buffer.
   * @param  len    Number of bytes.
   * @return true on success.
   */
  bool read(uint8_t* buffer, uint8_t len);

  /**
   * @brief  Read the register as an integer.
   * @return Value assembled according to the byte order (0 on I2C error).
   */
  uint32_t read(void);

  /**
   * @brief  Write raw bytes to the register.
   * @param  buffer Data to write.
   * @param  len    Number of bytes.
   * @return true on success.
   */
  bool write(const uint8_t* buffer, uint8_t len);

  /**
   * @brief  Write an integer to the register.
   * @param  value    Value to write.
   * @param  numbytes Bytes to send (0 = register width, max 4).
   * @return true on success.
   */
  bool write(uint32_t value, uint8_t numbytes = 0);

 private:
  Adafruit_I2CDevice* _dev; /**< Owning device. */
  uint16_t _reg;            /**< Register address. */
  uint8_t _width;           /**< Width in bytes. */
  uint8_t _order;           /**< MSBFIRST or LSBFIRST. */
};

/**
 * @brief A bit field inside an Adafruit_I2CRegister.
 */
class Adafruit_I2CRegisterBits {
 public:
  /**
   * @brief Constructor.
   * @param reg   Register containing the field.
   * @param bits  Field width in bits.
   * @param shift Position of the field's LSB within the register.
   */
  Adafruit_I2CRegisterBits(Adafruit_I2CRegister* reg, uint8_t bits,
                           uint8_t shift);

  /** @return The field value, right-aligned. */
  uint32_t read(void);

  /**
   * @brief  Read-modify-write the field.
   * @param  value New field value (extra high bits are masked off).
   * @return true on success.
   */
  bool write(uint32_t value);

 private:
  Adafruit_I2CRegister* _reg; /**< Register holding the field. */
  uint8_t _bits;              /**< Field width. */
  uint8_t _shift;             /**< Field position. */
};
