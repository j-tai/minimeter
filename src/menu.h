/*
 * Copyright (c) 2026 Jasmine Tai. All rights reserved.
 */

#ifndef MINIMETER_MENU_H
#define MINIMETER_MENU_H

#include <Arduino.h>

namespace menu {

/**
 * Represents a selectable item with multiple choices.
 *
 * Each item maintains a value, corresponding to the current selected choice,
 * and a set of choices, provided as a character array.
 */
struct Item {
    /// The currently selected index.
    uint8_t value = 0;
    uint8_t width = 1;
    const char* choices = nullptr;

    explicit Item() : choices(PSTR("")) {}
    explicit Item(const uint8_t width, const char* choices)
        : width(width), choices(choices) {}

    /**
     * Retrieves the currently selected choice from the list of choices.
     *
     * @return A pointer to program space, representing the current choice
     * string.
     */
    const char* get_current_choice() const { return choices + value * width; }

    /**
     * Retrieves the currently selected choice and writes it into the provided
     * output buffer.
     *
     * @param out A character buffer to store the current choice string. The
     * buffer must have space for at least 7 characters (6 for the choice and 1
     * for the null terminator).
     */
    void read_current_choice(char* out) const;
};

void set(uint8_t index, Item* item);

void loop();

} // namespace menu

#endif
