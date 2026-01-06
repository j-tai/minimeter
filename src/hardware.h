/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#ifndef MINIMETER_HARDWARE_H
#define MINIMETER_HARDWARE_H

#include <Arduino.h>

enum Pin : uint8_t {
    PIN_BUZZER = 2,
    PIN_SWITCH = 3,
    PIN_LED = LED_BUILTIN,
    PIN_INPUT_1 = A0,
    PIN_INPUT_1_PULL = 9,
    PIN_INPUT_2 = A1,
    PIN_INPUT_2_PULL = 8,
};

#endif
