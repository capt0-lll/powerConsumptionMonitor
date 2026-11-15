/**
 * @file    Adafruit_I2CRegister.cpp
 * @brief   Register and register-bit-field access implementation.
 */
#include "Adafruit_I2CRegister.h"

Adafruit_I2CRegister::Adafruit_I2CRegister(Adafruit_I2CDevice* dev,
                                           uint16_t reg, uint8_t width,
                                           uint8_t byteorder)
    : _dev(dev), _reg(reg), _width(width), _order(byteorder) {}

bool Adafruit_I2CRegister::read(uint8_t* buffer, uint8_t len) {
  uint8_t reg = (uint8_t)_reg;
  return _dev->write_then_read(&reg, 1, buffer, len);
}

uint32_t Adafruit_I2CRegister::read(void) {
  uint8_t buf[4];
  uint8_t n = _width > 4 ? 4 : _width;
  if (!read(buf, n)) return 0;
  uint32_t v = 0;
  for (uint8_t i = 0; i < n; i++) {
    uint8_t b = (_order == MSBFIRST) ? buf[i] : buf[n - 1 - i];
    v = (v << 8) | b;
  }
  return v;
}

bool Adafruit_I2CRegister::write(const uint8_t* buffer, uint8_t len) {
  uint8_t reg = (uint8_t)_reg;
  return _dev->write(buffer, len, &reg, 1);
}

bool Adafruit_I2CRegister::write(uint32_t value, uint8_t numbytes) {
  if (numbytes == 0) numbytes = _width;
  if (numbytes > 4) numbytes = 4;
  uint8_t buf[4];
  for (uint8_t i = 0; i < numbytes; i++) {
    uint8_t b = (uint8_t)(value >> (8 * i));
    buf[(_order == MSBFIRST) ? numbytes - 1 - i : i] = b;
  }
  return write(buf, numbytes);
}

Adafruit_I2CRegisterBits::Adafruit_I2CRegisterBits(Adafruit_I2CRegister* reg,
                                                   uint8_t bits, uint8_t shift)
    : _reg(reg), _bits(bits), _shift(shift) {}

uint32_t Adafruit_I2CRegisterBits::read(void) {
  uint32_t mask = (_bits >= 32) ? 0xFFFFFFFFu : ((1u << _bits) - 1u);
  return (_reg->read() >> _shift) & mask;
}

bool Adafruit_I2CRegisterBits::write(uint32_t value) {
  uint32_t mask = (_bits >= 32) ? 0xFFFFFFFFu : ((1u << _bits) - 1u);
  uint32_t cur = _reg->read();
  cur &= ~(mask << _shift);
  cur |= (value & mask) << _shift;
  return _reg->write(cur);
}
