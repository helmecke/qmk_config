#pragma once

#include QMK_KEYBOARD_H

#include "keymap_german.h"

// German-aware Caps Word policy. Compiled only when a keymap enables
// CAPS_WORD_ENABLE; the rest of the shared userspace does not depend on the
// core Caps Word API.
bool caps_word_press_user(uint16_t keycode);
