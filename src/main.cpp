/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include <Arduino.h>

#include "hardware.h"

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_INPUT_1, INPUT);
    pinMode(PIN_INPUT_1_PULL, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    digitalWrite(PIN_INPUT_1_PULL, HIGH);

    if (digitalRead(PIN_INPUT_1) == LOW) {
        digitalWrite(PIN_LED, HIGH);
        tone(PIN_BUZZER, 1000);
        delay(1);
    } else {
        digitalWrite(PIN_LED, LOW);
        noTone(PIN_BUZZER);
    }
}
