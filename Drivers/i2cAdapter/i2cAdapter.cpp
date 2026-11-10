/**
 * @file    i2cAdapter.cpp
 * @brief   Adapter initialisation.
 */
#include "i2cAdapter.h"

void i2cAdapterInit(I2C_HandleTypeDef* hi2c, uint32_t timeout_ms) {
  Wire.begin(hi2c);
  Wire.setTimeout(timeout_ms);
}
