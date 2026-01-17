/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "menu.h"

#include "hardware.h"

namespace menu {

constexpr uint8_t MAX_ITEMS = 4;

Item* items[MAX_ITEMS] = {nullptr};
uint8_t selected_index = 0;
uint8_t last_input = 0;

void set(const uint8_t index, Item* item) { items[index] = item; }

void loop() {
    const auto input = poll_input();
    const uint8_t new_input = input & ~last_input;

    if (new_input & BTN_SEL) {
        selected_index++;
    }

    if (items[selected_index] == nullptr) {
        selected_index = 0;
    }

    if (new_input & BTN_OK) {
        Item* item = items[selected_index];
        if (item != nullptr) {
            item->value++;
            if (item->value >= item->count) {
                item->value = 0;
            }
        }
    }

    last_input = input;
}

} // namespace menu
