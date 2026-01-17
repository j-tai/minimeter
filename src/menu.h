/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#ifndef MINIMETER_MENU_H
#define MINIMETER_MENU_H

#include <Arduino.h>

namespace menu {

struct Item {
    uint8_t value = 0;
    uint8_t count = 1;

    explicit Item(const uint8_t count) : count(count) {}
};

void set(uint8_t index, Item* item);

void loop();

} // namespace menu

#endif
