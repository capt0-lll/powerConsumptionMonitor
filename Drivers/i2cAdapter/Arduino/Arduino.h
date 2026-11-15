/**
 * @file    Arduino.h
 * @brief   Minimal Arduino.h replacement for STM32 HAL builds.
 *
 * Lets the unmodified Adafruit_INA228 sources compile, since they
 * include <Arduino.h>. Only the small subset they use is provided.
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stm32f3xx_hal.h"

#ifndef MSBFIRST
#define LSBFIRST 0 /**< Least significant byte first. */
#define MSBFIRST 1 /**< Most significant byte first. */
#endif

/**
 * @brief Blocking delay.
 * @param ms Delay length in milliseconds.
 */
void delay(uint32_t ms);
