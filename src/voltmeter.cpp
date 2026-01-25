/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "voltmeter.h"

#include <Arduino.h>

#include "hardware.h"
#include "lcd.h"
#include "menu.h"

namespace {
constexpr float SELF_VOLTAGE = 5.06F;
constexpr int NUM_MEASUREMENTS = UINT8_MAX + 1;

menu::Item mode;
uint8_t counter = 0;
float accumulator = 0.0F;
bool is_reverse = false;

constexpr float calculate_factor(const float resistance) {
    return (R_INPUT / resistance + 1.0F) * (SELF_VOLTAGE / 1023.0F);
}

float setup_pins() {
    reset_pins();

    const uint8_t reference = is_reverse ? HIGH : LOW;

    if (mode.value == 2) {
        pinMode(PIN_PULL_4K7, OUTPUT);
        digitalWrite(PIN_PULL_4K7, reference);
        return calculate_factor(R_PULL_4K7);
    }

    if (mode.value == 1) {
        pinMode(PIN_PULL_1K, OUTPUT);
        digitalWrite(PIN_PULL_1K, reference);
        return calculate_factor(R_PULL_1K);
    }

    pinMode(PIN_PULL_110, OUTPUT);
    digitalWrite(PIN_PULL_110, reference);
    return calculate_factor(R_PULL_110);
}
} // namespace

namespace voltmeter {
void setup() {
    lcd.clear();
    mode = menu::Item(7, PSTR("250V DC 40V DC 10V DC"));
    menu::set(1, &mode);
    counter = 0;
    accumulator = 0.0F;
}

void loop() {
    const float factor = setup_pins();

    // Account for stray capacitance that makes the digitalWrites a bit slow
    delayMicroseconds(30);

    if (counter == 0) {
        // Report the measurement
        const float voltage = accumulator / NUM_MEASUREMENTS;
        accumulator = 0.0F;

        lcd.setCursor(4, 0);
        char buffer[8];
        dtostrf(voltage, 6, mode.value, buffer);
        for (uint8_t i = strlen(buffer); i < 6; i++) {
            lcd.print(" ");
        }
        lcd.print(buffer);
        lcd.print(" V");
    }

    const int reading = analogRead(PIN_INPUT);
    if (is_reverse) {
        const float voltage = (reading - 1023) * factor + SELF_VOLTAGE;
        if (voltage <= 0.0F) {
            accumulator += voltage;
        } else {
            is_reverse = false;
        }
    } else {
        const float voltage = reading * factor;
        if (reading != 0) {
            accumulator += voltage;
        } else {
            is_reverse = true;
        }
    }
    counter++;
}
} // namespace voltmeter
