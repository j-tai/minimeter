/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#include "menu.h"

#include "hardware.h"
#include "lcd.h"

namespace menu {
constexpr uint8_t MAX_ITEMS = 2;

Item* items[MAX_ITEMS] = {nullptr};
uint8_t selected_index = 0;
uint8_t last_input = 0;
bool is_dirty = true;

void Item::read_current_choice(char out[7]) const {
    strncpy_P(out, get_current_choice(), CHOICE_LEN);
    out[CHOICE_LEN] = '\0';
}

namespace {
bool choice_is_overflowed(const Item& item) {
    auto chr = pgm_read_byte_near(item.get_current_choice());
    return chr == '\0';
}

void print_menu() {
    lcd.setCursor(0, 1);

    for (uint8_t i = 0; i < MAX_ITEMS; i++) {
        const Item* item = items[i];
        if (item == nullptr) {
            lcd.print("        ");
            continue;
        }

        char choice[Item::CHOICE_LEN + 1];
        item->read_current_choice(choice);

        if (selected_index == i) {
            lcd.print("[");
        } else {
            lcd.print(" ");
        }
        lcd.print(choice);
        if (selected_index == i) {
            lcd.print("]");
        } else {
            lcd.print(" ");
        }
    }
}
} // namespace

void set(const uint8_t index, Item* item) {
    items[index] = item;
    is_dirty = true;
}

void loop() {
    if (is_dirty) {
        print_menu();
        is_dirty = false;
    }

    const auto input = poll_input();
    const uint8_t new_input = input & ~last_input;

    if (new_input & BTN_SEL) {
        selected_index++;
        is_dirty = true;
    }

    if (items[selected_index] == nullptr) {
        selected_index = 0;
        is_dirty = true;
    }

    if (new_input & BTN_OK) {
        Item* item = items[selected_index];
        if (item != nullptr) {
            item->value++;
            if (choice_is_overflowed(*item)) {
                item->value = 0;
            }
        is_dirty = true;
        }
    }

    last_input = input;
}

} // namespace menu
