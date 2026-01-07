/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "hardware.h"

#include <Arduino.h>

constexpr unsigned int BUZZ_FREQUENCY = 1000;

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
                             | digitalRead(PIN_BUTTON_1)
                             | (digitalRead(PIN_BUTTON_2) << 1);
    return ~inverted;
}
