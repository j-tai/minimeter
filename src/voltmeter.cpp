/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "voltmeter.h"

#include <Arduino.h>

#include "hardware.h"

constexpr bool DEBUG = false;

namespace voltmeter {
    void setup() {
        buzz_off();
    }

    void loop() {
        pinMode(PIN_PULL, INPUT);
        const int reading = analogRead(PIN_INPUT);
        pinMode(PIN_PULL, OUTPUT);
        digitalWrite(PIN_PULL, HIGH);
        const int pullup_reading = analogRead(PIN_INPUT);
        digitalWrite(PIN_PULL, LOW);
        const int pulldown_reading = analogRead(PIN_INPUT);

        if (DEBUG) {
            Serial.print(reading);
            Serial.print(", up ");
            Serial.print(pullup_reading);
            Serial.print(", dn ");
            Serial.print(pulldown_reading);
            Serial.print(" = ");
        }

        if (pullup_reading >= 1000 && pulldown_reading < 24) {
            Serial.println("High impedance");
        } else {
            const float voltage = reading * 5.0F / 1023.0F;
            Serial.print(voltage, 2);
            Serial.println(" V");
        }
    }
}
