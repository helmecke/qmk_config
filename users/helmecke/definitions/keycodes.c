#include QMK_KEYBOARD_H

#include "keycodes.h"

uint16_t extract_tapping_keycode(uint16_t keycode) {
    // Return tapping keycode for tap dances
    switch (keycode) {
        case TD_COMM:
            return DE_COMM;
        default:
            break;
    }
    // Return tapping keycode for custom layer taps
    switch (keycode) {
        default:
            break;
    }
    // Return tapping keycode for basic mod taps
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            return keycode &= 0xff;
    }
    // Return tapping keycode for basic keycode
    return keycode;
}
