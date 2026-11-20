// Copyright 2026 Jakob Helmecke
// SPDX-License-Identifier: GPL-2.0-or-later

// The test fixture installs keycodes per test; this keymap only provides the
// array QMK keymap introspection needs, with a second layer for the thumb
// layer-tap case. The key override table is part of the keymap translation
// unit, exactly as on the keyboard.
#include QMK_KEYBOARD_H

#include "../../users/helmecke/helmecke.h"
#include "../../users/helmecke/definitions/keymap_tables.h"

// The keyboard build generates this weak default layout from the keyboard
// metadata; the test platform has none, but the weak default
// chordal_hold_handedness() still refers to it, so the fixture supplies it.
// The rule in effect is the userspace override with the same values on this
// test matrix: rows 0-1 left, row 2 right, row 3 and (2,5) exempt.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'},
    {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'},
    {'R', 'R', 'R', 'R', 'R', '*', 'R', 'R', 'R', 'R'},
    {'*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    },
    [1] = {
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
        {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    },
};
