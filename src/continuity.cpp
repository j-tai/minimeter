/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "continuity.h"

#include <Arduino.h>

#include "hardware.h"

namespace continuity {
    constexpr int SENSITIVITY = 4;

    void setup() {
        pinMode(PIN_PULL, OUTPUT);
        digitalWrite(PIN_PULL, HIGH);
    }

    void loop() {
        const int value = analogRead(PIN_INPUT);
        if (value <= 512 + SENSITIVITY) {
            buzz_on();
        } else {
            buzz_off();
        }
    }
}
