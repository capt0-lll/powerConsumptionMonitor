/**
 * @file    i2cAdapter.h
 * @brief   Entry point of the adapter that runs the unmodified Adafruit_INA228
 *          library (Arduino/BusIO based) on STM32 HAL.
 *
 * Modules (each in its own folder, added to the include path so the library's
 * `#include <Wire.h>` etc. resolve to these shims):
 *  - Arduino/              Arduino.h shim (delay, millis, MSBFIRST)
 *  - Wire/                 TwoWire on top of HAL I2C
 *  - Adafruit_I2CDevice/   BusIO device
 *  - Adafruit_I2CRegister/ BusIO register and register bits
 *
 * @code
 * #include "i2cAdapter.h"
 * #include "Adafruit_INA228.h"
 * extern I2C_HandleTypeDef hi2c1;
 *
 * Adafruit_INA228 ina;
 * i2cAdapterInit(&hi2c1);
 * ina.begin(0x40);   // uses the global Wire
 * @endcode
 */
#pragma once

#include "Adafruit_I2CDevice.h"
#include "Adafruit_I2CRegister.h"
#include "Arduino.h"
#include "Wire.h"

/**
 * @brief Bind the global Wire to a CubeMX I2C handle.
 * @param hi2c       Handle initialised by HAL_I2C_Init() (e.g. &hi2c1).
 * @param timeout_ms Timeout for every transfer, in milliseconds.
 */
void i2cAdapterInit(I2C_HandleTypeDef* hi2c, uint32_t timeout_ms = 100);
