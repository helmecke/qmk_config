#include QMK_KEYBOARD_H

#include "german_us.h"

process_record_result_t process_german_us(uint16_t keycode, keyrecord_t *record) {
    if (record != NULL && !record->event.pressed) {
        return PROCESS_RECORD_CONTINUE;
    }

    uint8_t saved_mods = get_mods();

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
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(DE_MINS);
                    set_mods(saved_mods);
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
                    tap_code16(DE_LCBR);
                    set_mods(saved_mods);
                } else {
                    tap_code16(DE_LBRC);
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        case U_RBRC:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(DE_RCBR);
                    set_mods(saved_mods);
                } else {
                    tap_code16(DE_RBRC);
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
    }

    return PROCESS_RECORD_CONTINUE;
}
