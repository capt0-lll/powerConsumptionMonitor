/**
 * @file    Arduino.cpp
 * @brief   Arduino timing functions implemented with the STM32 HAL tick.
 */
#include "Arduino.h"

void delay(uint32_t ms) { HAL_Delay(ms); }
