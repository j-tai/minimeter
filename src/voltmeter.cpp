/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "voltmeter.h"

#include <Arduino.h>

#include "hardware.h"
#include "menu.h"

namespace {
constexpr uint8_t BUFFER_SIZE = 16;
constexpr uint8_t INDEX_MASK = BUFFER_SIZE - 1;
constexpr int NUM_MEASUREMENTS = 256;

menu::Item mode;
uint8_t counter = 0;
float buffer[BUFFER_SIZE] = {};

constexpr float calculate_factor(const float resistance) {
    return (R_INPUT / resistance + 1.0F) * (5.0F / 1023.0F / NUM_MEASUREMENTS);
}

float setup_pins() {
    reset_pins();

    if (mode.value == 2) {
        pinMode(PIN_PULL_10K, OUTPUT);
        digitalWrite(PIN_PULL_10K, LOW);
        return calculate_factor(R_PULL_10K);
    }

    if (mode.value == 1) {
        pinMode(PIN_PULL_1K, OUTPUT);
        digitalWrite(PIN_PULL_1K, LOW);
        return calculate_factor(R_PULL_1K);
    }

    pinMode(PIN_PULL_110, OUTPUT);
    digitalWrite(PIN_PULL_110, LOW);
    return calculate_factor(R_PULL_110);
}

float sum_and_clear_buffer() {
    float sum = 0;
    for (float& entry : buffer) {
        sum += entry;
        entry = 0.0F;
    }
    return sum;
}
} // namespace

namespace voltmeter {
void setup() {
    mode.choices = PSTR("250VDC 50VDC 10VDC");
    menu::set(1, &mode);
    counter = 0;
    sum_and_clear_buffer();
}

void loop() {
    const float factor = setup_pins();

    if (counter == 0) {
        // Report the measurement
        const float voltage = sum_and_clear_buffer() * factor;
        Serial.print(voltage, mode.value);
        Serial.println(" V");
    }

    const uint8_t index = counter & INDEX_MASK;
    buffer[index] += analogRead(PIN_INPUT);
    counter++;
}
} // namespace voltmeter
