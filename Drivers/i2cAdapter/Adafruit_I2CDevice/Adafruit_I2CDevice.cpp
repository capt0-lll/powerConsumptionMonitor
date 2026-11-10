/**
 * @file    Adafruit_I2CDevice.cpp
 * @brief   Adafruit_I2CDevice implementation.
 */
#include "Adafruit_I2CDevice.h"

#include <string.h>

Adafruit_I2CDevice::Adafruit_I2CDevice(uint8_t addr, TwoWire* wire)
    : _addr(addr), _wire(wire) {}

bool Adafruit_I2CDevice::begin() { return _wire->probe(_addr); }

bool Adafruit_I2CDevice::write(const uint8_t* buffer, size_t len,
                               const uint8_t* prefix, size_t prefix_len) {
  uint8_t tmp[16];
  if (prefix_len + len > sizeof(tmp)) return false;
  if (prefix_len) memcpy(tmp, prefix, prefix_len);
  if (len) memcpy(tmp + prefix_len, buffer, len);
  return _wire->write(_addr, tmp, prefix_len + len);
}

bool Adafruit_I2CDevice::write_then_read(const uint8_t* wbuf, size_t wlen,
                                         uint8_t* rbuf, size_t rlen) {
  return _wire->writeRead(_addr, wbuf, wlen, rbuf, rlen);
}
