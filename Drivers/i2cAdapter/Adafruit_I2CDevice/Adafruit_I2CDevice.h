/**
 * @file    Adafruit_I2CDevice.h
 * @brief   Subset of Adafruit BusIO's Adafruit_I2CDevice, backed by TwoWire.
 */
#pragma once

#include "Wire.h"

/**
 * @brief A single I2C slave on a TwoWire bus.
 */
class Adafruit_I2CDevice {
 public:
  /**
   * @brief Constructor.
   * @param addr 7-bit device address.
   * @param wire Bus to use (defaults to the global Wire).
   */
  Adafruit_I2CDevice(uint8_t addr, TwoWire* wire);

  /**
   * @brief  Check that the device acknowledges its address.
   * @return true if the device responded.
   */
  bool begin();

  /**
   * @brief  Write bytes to the device.
   * @param  buffer     Data to send.
   * @param  len        Number of bytes in @p buffer.
   * @param  prefix     Optional bytes sent before @p buffer.
   * @param  prefix_len Number of prefix bytes (prefix + data max 16).
   * @return true on success.
   */
  bool write(const uint8_t* buffer, size_t len,
             const uint8_t* prefix = nullptr, size_t prefix_len = 0);

  /**
   * @brief  Write bytes, then read bytes.
   * @param  wbuf Bytes to write.
   * @param  wlen Number of bytes to write.
   * @param  rbuf Destination for the bytes read.
   * @param  rlen Number of bytes to read.
   * @return true on success.
   */
  bool write_then_read(const uint8_t* wbuf, size_t wlen, uint8_t* rbuf,
                       size_t rlen);

 private:
  uint8_t _addr;    /**< 7-bit address. */
  TwoWire* _wire;   /**< Bus the device is on. */
};
