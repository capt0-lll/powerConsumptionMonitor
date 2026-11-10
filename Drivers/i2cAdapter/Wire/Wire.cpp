/**
 * @file    Wire.cpp
 * @brief   TwoWire implementation using blocking STM32 HAL I2C calls.
 */
#include "Wire.h"

TwoWire Wire;

/** @brief Convert a 7-bit address to the HAL's left-aligned form. */
static inline uint16_t hal_addr(uint8_t a7) { return (uint16_t)(a7 << 1); }

TwoWire::TwoWire() : _h(nullptr), _timeout(100) {}

void TwoWire::begin(I2C_HandleTypeDef *h) { _h = h; }

void TwoWire::setTimeout(uint32_t ms) { _timeout = ms; }

bool TwoWire::probe(uint8_t a) {
  return _h && HAL_I2C_IsDeviceReady(_h, hal_addr(a), 3, _timeout) == HAL_OK;
}

bool TwoWire::write(uint8_t a, const uint8_t *buf, size_t len) {
  return _h && HAL_I2C_Master_Transmit(_h, hal_addr(a), (uint8_t *)buf,
                                       (uint16_t)len, _timeout) == HAL_OK;
}

bool TwoWire::read(uint8_t a, uint8_t *buf, size_t len) {
  return _h && HAL_I2C_Master_Receive(_h, hal_addr(a), buf, (uint16_t)len,
                                      _timeout) == HAL_OK;
}

bool TwoWire::writeRead(uint8_t a, const uint8_t *w, size_t wlen, uint8_t *r,
                        size_t rlen) {
  if (!_h)
    return false;
  if (wlen == 1) // register pointer + repeated start
    return HAL_I2C_Mem_Read(_h, hal_addr(a), w[0], I2C_MEMADD_SIZE_8BIT, r,
                            (uint16_t)rlen, _timeout) == HAL_OK;
  return write(a, w, wlen) && read(a, r, rlen);
}
