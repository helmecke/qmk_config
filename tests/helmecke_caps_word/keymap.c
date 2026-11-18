// Copyright 2026 Jakob Helmecke
// SPDX-License-Identifier: GPL-2.0-or-later

// The test fixture installs keycodes per test; this keymap only provides the
// array QMK keymap introspection needs. The tap dance and key override tables
// are part of the keymap translation unit, exactly as on the keyboard.
#include QMK_KEYBOARD_H

#include "../../users/helmecke/helmecke.h"
#include "../../users/helmecke/definitions/keymap_tables.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    },
};
