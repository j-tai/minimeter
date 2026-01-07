/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include <Arduino.h>

#include "continuity.h"
#include "hardware.h"
#include "voltmeter.h"

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_BUTTON_1, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_INPUT, INPUT);

    Serial.begin(9600);
    Serial.println("----- RESET -----");
}

uint8_t last_input = 0;

bool should_switch_mode() {
    const auto input = poll_input();
    const bool result = (input & ~last_input) & BTN_1;
    last_input = input;
    return result;
}

void loop() {
    // Continuity mode
    continuity::setup();
    while (!should_switch_mode()) {
        continuity::loop();
    }

    // Voltmeter mode
    voltmeter::setup();
    while (!should_switch_mode()) {
        voltmeter::loop();
    }
}
