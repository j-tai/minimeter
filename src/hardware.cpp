/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "hardware.h"

#include <Arduino.h>

constexpr unsigned int BUZZ_FREQUENCY = 1000;

void reset_pins() {
    buzz_off();
    pinMode(PIN_INPUT, INPUT);
    pinMode(PIN_PULL_10K, INPUT);
    pinMode(PIN_PULL_1K, INPUT);
    pinMode(PIN_PULL_110, INPUT);
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
    const uint8_t inverted = 0xFC
                             | digitalRead(PIN_BUTTON_MODE)
                             | (digitalRead(PIN_BUTTON_OK) << 1);
    return ~inverted;
}
