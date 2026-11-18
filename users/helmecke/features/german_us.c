#include QMK_KEYBOARD_H

#include "german_us.h"

#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#endif // CAPS_WORD_ENABLE

// Keycodes whose output is produced here instead of by the action layer. They
// are all punctuation or dead keys, so they end Caps Word before they emit:
// core Caps Word never sees these events because this handler consumes them.
static bool is_custom_punctuation(uint16_t keycode) {
    switch (keycode) {
        case HB_QUOT:
        case U_SLSH:
        case U_LBRC:
        case U_RBRC:
        case DE_AT:
        case DE_GRV:
        case DE_CIRC:
        case DE_TILD:
        case DE_BSLS:
        case DE_PIPE:
        case DE_LCBR:
        case DE_RCBR:
        case DE_LBRC:
        case DE_RBRC:
            return true;
        default:
            return false;
    }
}

process_record_result_t process_german_us(uint16_t keycode, keyrecord_t *record) {
    if (record != NULL && !record->event.pressed) {
        return PROCESS_RECORD_CONTINUE;
    }

    uint8_t saved_mods = get_mods();
    bool    is_mac     = helmecke_os_is_apple();

#ifdef CAPS_WORD_ENABLE
    if (record != NULL && is_custom_punctuation(keycode)) {
        // Terminate before emitting. Caps Word's weak Shift must not leak into
        // the punctuation, and the mode has to end even though the event does
        // not reach core Caps Word.
        caps_word_off();
    }
#endif // CAPS_WORD_ENABLE

    switch (keycode) {
        case HB_QUOT:
            if (record->tap.count && record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    tap_code16(DE_DQUO);
                } else {
                    tap_code16(DE_QUOT);
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case U_SZ:
            if (record->event.pressed) {
#ifdef CAPS_WORD_ENABLE
                if (is_caps_word_on()) {
                    // The dedicated ß key types the capital form "SS" while Caps
                    // Word is active, like the AltGr+S override. This event is
                    // consumed here and never reaches core Caps Word, so its
                    // weak Shift is not available: apply Shift to the synthetic
                    // S keystrokes explicitly.
                    tap_code16(S(DE_S));
                    tap_code16(S(DE_S));
                    return PROCESS_RECORD_RETURN_FALSE;
                }
#endif // CAPS_WORD_ENABLE
                tap_code16(DE_SS);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case U_SLSH:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    tap_code16(DE_SS);
                } else {
                    tap_code16(DE_SLSH);
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case U_LBRC:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    if (is_mac) {
                        register_mods(MOD_BIT(KC_RALT));
                        tap_code16(DE_8);
                    } else {
                        tap_code16(DE_LCBR);
                    }
                    set_mods(saved_mods);
                } else {
                    if (is_mac) {
                        register_mods(MOD_BIT(KC_RALT));
                        tap_code16(DE_5);
                        set_mods(saved_mods);
                    } else {
                        tap_code16(DE_LBRC);
                    }
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case U_RBRC:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    if (is_mac) {
                        register_mods(MOD_BIT(KC_RALT));
                        tap_code16(DE_9);
                    } else {
                        tap_code16(DE_RCBR);
                    }
                    set_mods(saved_mods);
                } else {
                    if (is_mac) {
                        register_mods(MOD_BIT(KC_RALT));
                        tap_code16(DE_6);
                        set_mods(saved_mods);
                    } else {
                        tap_code16(DE_RBRC);
                    }
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_AT:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_L);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_GRV:
            if (record->event.pressed) {
                if (is_mac) {
                    tap_code16(DE_GRV);
                    tap_code16(KC_SPC);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_CIRC:
            if (record->event.pressed) {
                if (is_mac) {
                    tap_code16(DE_CIRC);
                    tap_code16(KC_SPC);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_TILD:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_N);
                    set_mods(saved_mods);
                    tap_code16(KC_SPC);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_BSLS:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT) | MOD_BIT(KC_RSFT));
                    tap_code16(DE_7);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_PIPE:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_7);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_LCBR:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_8);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_RCBR:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_9);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_LBRC:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_5);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case DE_RBRC:
            if (record->event.pressed) {
                if (is_mac) {
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code16(DE_6);
                    set_mods(saved_mods);
                } else {
                    return PROCESS_RECORD_CONTINUE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
    }

    return PROCESS_RECORD_CONTINUE;
}
