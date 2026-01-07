/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#ifndef MINIMETER_HARDWARE_H
#define MINIMETER_HARDWARE_H

#include <Arduino.h>

enum Pin : uint8_t {
    PIN_BUZZER = 2,
    PIN_BUTTON_1 = 3,
    PIN_BUTTON_2 = 4,
    PIN_LED = LED_BUILTIN,
    PIN_INPUT = A0,
    PIN_PULL = 9,
};

enum Input : uint8_t {
    BTN_1 = 0x1,
    BTN_2 = 0x2,
};

void buzz_on();

void buzz_off();

uint8_t poll_input();

#endif
