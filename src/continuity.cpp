/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "continuity.h"

#include <Arduino.h>

#include "hardware.h"
#include "lcd.h"
#include "menu.h"

namespace continuity {
constexpr int SENSITIVITY = 4;
bool last_value = false;

void setup() {
    lcd.clear();
    menu::set(1, nullptr);
    last_value = false;
    pinMode(PIN_PULL_10K, OUTPUT);
    digitalWrite(PIN_PULL_10K, HIGH);
}

void loop() {
    const bool value = analogRead(PIN_INPUT) <= 512 + SENSITIVITY;

    if (value != last_value) {
        if (value) {
            buzz_on();
        } else {
            buzz_off();
        }

        lcd.setCursor(2, 0);
        lcd.print(value ? "!CONTINUITY!" : "            ");
    }

    last_value = value;
}
} // namespace continuity
