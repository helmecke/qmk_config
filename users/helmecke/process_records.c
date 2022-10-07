/*
Copyright 2022 Jakob Helmecke @helmecke

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "helmecke.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("pru: 0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
         keycode,
         record->event.key.row,
         record->event.key.col,
         get_highest_layer(layer_state),
         record->event.pressed,
         get_mods(),
         get_oneshot_mods(),
         record->tap.count
    );
#endif

    bool return_state = true;
    uint8_t saved_mods = get_mods();

#ifdef CUSTOM_LEADER_ENABLE
    if (!process_leader(keycode, record)) {
        return false;
    }
#endif
#ifdef CUSTOM_REPEAT_ENABLE
    process_repeat_key(keycode, record);
#endif /* CUSTOM_REPEAT_ENABLE */
    switch (keycode) {
        // US like KC_QUOT with mod-tap
        case U_QUOT:
            if (record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    tap_code16(DE_DQUO);
                } else {
                    tap_code16(DE_QUOT);
                }
                return_state = false;
                break;
            }
            break;
        case HB_QUOT:
            if (record->tap.count && record->event.pressed) {
                if (saved_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                    tap_code16(DE_DQUO);
                } else {
                    tap_code16(DE_QUOT);
                }
                return_state = false;
                break;
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
                return_state = false;
                break;
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
                return_state = false;
                break;
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
                return_state = false;
                break;
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
                return_state = false;
                break;
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
                return_state = false;
                break;
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
                return_state = false;
                break;
            }
            break;
#ifdef CUSTOM_LEADER_ENABLE
        case LEADER:
            if (record->event.pressed) {
                start_leading();
            }
            return_state = false;
            break;
#endif
    }
    return return_state;
}
