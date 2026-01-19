/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "continuity.h"

#include <Arduino.h>

#include "hardware.h"
#include "menu.h"

namespace continuity {
constexpr int SENSITIVITY = 4;

void setup() {
    pinMode(PIN_PULL_10K, OUTPUT);
    digitalWrite(PIN_PULL_10K, HIGH);
    menu::set(1, nullptr);
}

void loop() {
    const int value = analogRead(PIN_INPUT);
    if (value <= 512 + SENSITIVITY) {
        buzz_on();
    } else {
        buzz_off();
    }
}
} // namespace continuity
