/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "continuity.h"

#include <Arduino.h>

#include "hardware.h"
#include "lcd.h"
#include "menu.h"

namespace continuity {
constexpr int TARGET_READING =
    static_cast<int>(1023 * R_INPUT / (R_INPUT + R_PULL_4K7));
constexpr int SENSITIVITY = 5;
bool last_value = false;

void setup() {
    lcd.clear();
    reset_pins();
    menu::set(1, nullptr);
    last_value = false;
    pinMode(PIN_PULL_4K7, OUTPUT);
    digitalWrite(PIN_PULL_4K7, HIGH);
}

void loop() {
    const bool value = analogRead(PIN_INPUT) <= TARGET_READING + SENSITIVITY;

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
