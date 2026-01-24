/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "lcd.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace {
constexpr bool DEBUG = false;
constexpr uint8_t LCD_ADDRESS = 0x27;
} // namespace

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void lcd_init() {
    if (DEBUG) {
        Wire.begin();
        Serial.println("Scanning...");
        for (uint8_t addr = 1; addr < 127; addr++) {
            Wire.beginTransmission(addr);
            if (Wire.endTransmission() == 0) {
                Serial.print("Found device at address 0x");
                Serial.println(addr, HEX);
            }
        }
        Serial.println("Scan complete.");
        Wire.end();
    }

    lcd.init();
    lcd.backlight();
}
