/**
 * @file    Wire.h
 * @brief   Minimal Arduino TwoWire implementation on top of STM32 HAL I2C.
 */
#pragma once

#include "Arduino.h"

/**
 * @brief I2C bus master compatible with the parts of Arduino's TwoWire
 *        used by the Adafruit libraries.
 *
 * All addresses are 7-bit; the shift required by the HAL is done internally.
 * Every transfer is blocking and returns false on any HAL error or timeout.
 */
class TwoWire {
 public:
  /**
   * @brief Constructor. The bus is unbound until begin() is called.
   */
  TwoWire();

  /**
   * @brief Bind the bus to a CubeMX-generated handle (e.g. &hi2c1).
   * @param h I2C handle, already initialised by HAL_I2C_Init().
   */
  void begin(I2C_HandleTypeDef* h);

  /**
   * @brief Set the timeout used for every transfer.
   * @param ms Timeout in milliseconds.
   */
  void setTimeout(uint32_t ms);

  /**
   * @brief  Check whether a device acknowledges its address.
   * @param  addr7 7-bit device address.
   * @return true if the device responded.
   */
  bool probe(uint8_t addr7);

  /**
   * @brief  Write a buffer to a device.
   * @param  addr7 7-bit device address.
   * @param  buf   Data to send.
   * @param  len   Number of bytes.
   * @return true on success.
   */
  bool write(uint8_t addr7, const uint8_t* buf, size_t len);

  /**
   * @brief  Read bytes from a device.
   * @param  addr7 7-bit device address.
   * @param  buf   Destination buffer.
   * @param  len   Number of bytes to read.
   * @return true on success.
   */
  bool read(uint8_t addr7, uint8_t* buf, size_t len);

  /**
   * @brief  Write bytes, then read bytes.
   *
   * When @p wlen is 1 (register pointer) a repeated start is used;
   * otherwise a stop condition is issued between the phases.
   *
   * @param  addr7 7-bit device address.
   * @param  wbuf  Bytes to write.
   * @param  wlen  Number of bytes to write.
   * @param  rbuf  Destination for the bytes read.
   * @param  rlen  Number of bytes to read.
   * @return true on success.
   */
  bool writeRead(uint8_t addr7, const uint8_t* wbuf, size_t wlen, uint8_t* rbuf,
                 size_t rlen);

 private:
  I2C_HandleTypeDef* _h; /**< Bound HAL I2C handle. */
  uint32_t _timeout;     /**< Transfer timeout in ms. */
};

/** @brief Global bus, the default `theWire` argument of the Adafruit driver. */
extern TwoWire Wire;
