/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#ifndef MINIMETER_HARDWARE_H
#define MINIMETER_HARDWARE_H

#include <Arduino.h>

/// Pin numbers.
enum Pin : uint8_t {
    PIN_BUZZER = 2,
    PIN_BUTTON_OK = 3,
    PIN_BUTTON_MODE = 4,
    PIN_LED = LED_BUILTIN,
    PIN_INPUT = A0,
    PIN_PULL_4K7 = 9,
    PIN_PULL_1K = 8,
    PIN_PULL_100 = 7,
};

/// Resistance of the input pin.
constexpr float R_INPUT = 10000.0F;
constexpr float R_PULL_4K7 = 4700.0F;
constexpr float R_PULL_1K = 1000.0F;
constexpr float R_PULL_100 = 100.0F;

enum Input : uint8_t {
    BTN_SEL = 0x1,
    BTN_OK = 0x2,
};

void reset_pins();

void buzz_on();

void buzz_off();

uint8_t poll_input();

#endif
