/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "hardware.h"

#include <Arduino.h>

namespace {
constexpr unsigned int BUZZ_FREQUENCY = 1000;
uint8_t last_input = 0;
} // namespace

void reset_pins() {
    buzz_off();
    pinMode(PIN_INPUT, INPUT);
    pinMode(PIN_PULL_4K7, INPUT);
    pinMode(PIN_PULL_1K, INPUT);
    pinMode(PIN_PULL_100, INPUT);
}

void buzz_on() {
    digitalWrite(PIN_LED, HIGH);
    tone(PIN_BUZZER, BUZZ_FREQUENCY);
}

void buzz_off() {
    digitalWrite(PIN_LED, LOW);
    noTone(PIN_BUZZER);
}

uint8_t poll_input() {
    const uint8_t inverted =
        digitalRead(PIN_BUTTON_MODE) | (digitalRead(PIN_BUTTON_OK) << 1);
    const uint8_t current = inverted ^ (BTN_SEL | BTN_OK);
    // Debounce: require 2 readings in a row
    const uint8_t result = last_input & current;
    last_input = current;
    return result;
}
