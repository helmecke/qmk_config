#include QMK_KEYBOARD_H

#include "german_us.h"

process_record_result_t process_german_us(uint16_t keycode, keyrecord_t *record) {
    if (record != NULL && !record->event.pressed) {
        return PROCESS_RECORD_CONTINUE;
    }

    uint8_t saved_mods = get_mods();
    bool    is_mac     = detected_host_os() == OS_MACOS;

    switch (keycode) {
        case U_QUOT:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    tap_code16(DE_DQUO);
                } else {
                    tap_code16(DE_QUOT);
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
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
        case U_SCLN:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(DE_COLN);
                    set_mods(saved_mods);
                } else {
                    tap_code16(DE_SCLN);
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case HB_SCLN:
            if (record->tap.count && record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(DE_COLN);
                    set_mods(saved_mods);
                } else {
                    tap_code16(DE_SCLN);
                }
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
        case U_PLUS:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(DE_EQL);
                    set_mods(saved_mods);
                } else {
                    tap_code16(DE_PLUS);
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
