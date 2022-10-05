/* Copyright 2022 @vvhg1
 * Original author: @andrewjrae
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "leaderfuncs.h"
#include "keycodes.h"
#include "keymap_german.h"

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_A:
            tap_code16(DE_ADIA);
            break;
        case KC_O:
            tap_code16(DE_ODIA);
            break;
        case KC_S:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
            }
            tap_code16(DE_SS);
            break;
        case KC_U:
            tap_code16(DE_UDIA);
            break;
#ifdef CAPS_WORD_ENABLE
        case KC_C:
            caps_word_toggle();
            break;
#endif
        case KC_LSHIFT:
        case KC_RSHIFT:
            // escape shift modifier
            return leader_start_func;
        default:
            return NULL;
    }
    return NULL;
}
