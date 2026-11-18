#include QMK_KEYBOARD_H

#include "caps_word_german.h"

#include "action_util.h"

// Policy callback for QMK's built-in Caps Word. It is the single source of
// truth for whether a key continues the word; core Caps Word decides when the
// word ends.
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Letters continue the word with Caps Word's weak Shift applied. The
        // German umlaut positions are letters too, even though they fall
        // outside KC_A...KC_Z, and so does the German minus key: Caps Word
        // types it as underscore.
        case KC_A ... KC_Z:
        case DE_ADIA:
        case DE_ODIA:
        case DE_UDIA:
        case DE_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        // Digits and editing keys continue the word without shift.
        case KC_1 ... KC_0:
        case DE_UNDS:
        case KC_BSPC:
        case KC_DEL:
            return true;

        default:
            return false;
    }
}
