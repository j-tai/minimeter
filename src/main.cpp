/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include <Arduino.h>

#include "continuity.h"
#include "hardware.h"
#include "menu.h"
#include "voltmeter.h"

uint8_t last_mode = -1;
menu::Item mode_selection;

void setup() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_BUTTON_MODE, INPUT_PULLUP);
    pinMode(PIN_BUTTON_OK, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_INPUT, INPUT);

    mode_selection.choices = PSTR("ContinVoltag");
    menu::set(0, &mode_selection);

    Serial.begin(9600);
    Serial.println(F("----- RESET -----"));
}

void loop() {
    menu::loop();

    const auto mode = mode_selection.value;
    const auto should_setup = mode != last_mode;

    if (mode == 0) {
        if (should_setup)
            continuity::setup();
        continuity::loop();
    } else if (mode == 1) {
        if (should_setup)
            voltmeter::setup();
        voltmeter::loop();
    }
}
