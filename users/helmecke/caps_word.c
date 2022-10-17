#include "caps_word.h"
#include "layers.h"
#include "keymap_german.h"

caps_word_mode_t g_caps_word_mode = CAPS_WORD_MODE_DEFAULT;
bool g_caps_word_last_key_was_space = false;

bool caps_word_press_user(uint16_t keycode) {
    switch(g_caps_word_mode) {
        case CWMODE_NORMAL:
            switch (keycode) {
                // Keycodes that continue Caps Word, with shift applied.
                case DE_A ... DE_Z:
                case DE_MINS:
                    add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
                    return true;

                // Keycodes that continue Caps Word, without shifting.
                case DE_1 ... DE_0:
                case KC_BSPC:
                case KC_DEL:
                case DE_UNDS:
                    return true;

                default:
                    return false;  // Deactivate Caps Word.
            }
        case CWMODE_NUM_LOCK:
            switch (keycode) {
                // Keycodes that continue Caps Word, without shifting.
                case DE_1 ... DE_0:
                case DE_DOT:
                case DE_COMM:
                case KC_BSPC:
                    return true;

                default:
                    return false;  // Deactivate Caps Word.
            }
        case CWMODE_ARROW_SHIFT:
            switch (keycode) {
                // Keycodes that continue Caps Word, without shifting.
                case KC_LEFT:
                case KC_RIGHT:
                case KC_UP:
                case KC_DOWN:
                case A(KC_LEFT):
                case A(KC_RIGHT):
                case A(KC_UP):
                case A(KC_DOWN):
                case G(KC_LEFT):
                case G(KC_RIGHT):
                case G(KC_UP):
                case G(KC_DOWN):
                    add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
                    return true;

                default:
                    return false;  // Deactivate Caps Word.
            }
        case CWMODE_CONSTANT_CASE:
        case CWMODE_KEBAB_CASE:
        case CWMODE_SNAKE_CASE:
        case CWMODE_CAMEL_CASE:
        case CWMODE_SLASH_CASE:
            switch (keycode) {
                case KC_SPC:
                    // If the last key was NOT a space, then register it having been pressed and
                    // move on as normal
                    if (!g_caps_word_last_key_was_space) {
                        g_caps_word_last_key_was_space = true;
                        return true;
                    }
                    // if this is the second space in a row, delete one and exit Caps Word
                    else {
                        tap_code16(KC_BSPC);
                        return false;
                    }

                // Keys that do NOT break the Caps Word state
                case DE_A ... DE_Z:
                case DE_1 ... DE_0:
                case DE_MINS:
                case DE_UNDS:
                case KC_BSPC:
                    // If we're continuing on after a space, then we need to "address" that prior
                    // space in some way. The way we do that depends on what mode we're in. But
                    // in all cases, first we need to remove that space and then replace it with
                    // another character or another operating mode (ex. OSM)
                    if (g_caps_word_last_key_was_space) {
                        tap_code16(KC_BSPC);
                        switch (g_caps_word_mode) {
                            case CWMODE_CONSTANT_CASE:
                            case CWMODE_SNAKE_CASE:
                                tap_code16(DE_UNDS);
                                break;
                            case CWMODE_KEBAB_CASE:
                                tap_code16(DE_MINS);
                                break;
                            case CWMODE_SLASH_CASE:
                                tap_code16(DE_SLSH);
                                break;
                            case CWMODE_CAMEL_CASE:
                                add_oneshot_mods(MOD_LSFT);
                                break;
                            default:
                                break;

                        }
                        g_caps_word_last_key_was_space = false;
                    }
                    // If we're in CONSTANT_CASE, then we need to upper case letters
                    if (
                        g_caps_word_mode == CWMODE_CONSTANT_CASE
                        && (DE_A <= keycode && keycode <= DE_Z)
                    ) {
                        add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
                    }
                    return true;

                default:
                    return false;  // Deactivate Caps Word
            }

        default:
            return false;
    }
}

void caps_word_set_user(bool active) {
    if (active) {
        // Do something when Caps Word activates.
        g_caps_word_last_key_was_space = false;
    } else {
        // If leaving the num_lock mode, then we need to exit that layer
        // Do something when Caps Word deactivates.
        if (g_caps_word_mode == CWMODE_NUM_LOCK) {
            layer_off(_NUM);  // leave the numbers layer
        }
        // Go back to make sure that when it turns on next without any sepcification (ex. through
        // the CAPS_WORD key), it's in the default caps_word mode
        g_caps_word_mode = CAPS_WORD_MODE_DEFAULT;
    }
}

// Toggles caps word for the given mode. If that mode is already on, then it's getting turned off.
// If it's a new mode (or caps word isn't on at all), the old one will cycle off, then the new
// one will turn on. Returns true if caps word (in any mode) is on after the call.
bool toggle_caps_word_mode(caps_word_mode_t new_mode) {
    // remember the old settings before we turn it off since that will clear these values
    bool caps_word_was_off = !is_caps_word_on();
    caps_word_mode_t prior_mode = g_caps_word_mode;
    // want to cycle it off, regardless of whether we're going to turn something else on, so that
    // any "wrap up code" (ex. function caps_word_set_user) can execute between the change.
    caps_word_off();
    // if it wasn't on (and thus we're toggling it on) or we're going into a new mode
    if (caps_word_was_off || prior_mode != new_mode) {
        caps_word_on();
        g_caps_word_mode = new_mode;
        // if we're going into num_lock, then switch into the numbers layer
        if (g_caps_word_mode == CWMODE_NUM_LOCK) {
            layer_on(_NUM);
        }
    }
    return is_caps_word_on();
}
