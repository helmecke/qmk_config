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

#pragma once

// Used to extract the basic tapping keycode from a dual-role key.
// Example: GET_TAP_KC(MT(MOD_RSFT, KC_E)) == KC_E
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF

// Left-hand home row mods
#define HB_A LGUI_T(DE_A)
#define HB_S LALT_T(DE_S)
#define HB_D LSFT_T(DE_D)
#define HB_F LCTL_T(DE_F)
#define HB_X ALGR_T(DE_X)

// Right-hand home row mods
#define HB_J RCTL_T(DE_J)
#define HB_K RSFT_T(DE_K)
#define HB_L LALT_T(DE_L)
#define HB_QUOT RGUI_T(U_QUOT)
#define HB_SCLN RGUI_T(U_SCLN)
#define HB_DOT ALGR_T(DE_DOT)

// Left-thumb
#define TH_ESC LT(_MOUSE, KC_ESC)
#define TH_BSPC LT(_SYM, KC_BSPC)
#define TH_TAB LT(_NAV, KC_TAB)

// Right-thumb
#define TH_ENT LT(_MOUSE, KC_ENT)
#define TH_SPC LT(_NUM, KC_SPC)
#define FUN_TAB LT(_FUN, KC_TAB)

#ifdef TAP_DANCE_ENABLE
    #define U_RST TD(TD_RESET)
    #define U_DOT TD(TD_DOT)
    #define U_MINS TD(TD_MINS)
    #define U_LEAD TD(TD_LEAD)
    #define U_DBG QK_DEBUG_TOGGLE
#else
    #define U_RST QK_BOOT
    #define U_DOT _______
    #define U_MINS _______
    #define U_LEAD DE_COMM
    #define U_DBG QK_DEBUG_TOGGLE
#endif

#define OS_CTL OSM(MOD_LCTL)
#define OS_SFT OSM(MOD_LSFT)
#define OS_ALT OSM(MOD_LALT)
#define OS_GUI OSM(MOD_LGUI)
#define OS_ALGR OSM(MOD_RALT)
#define OS_NSYM OSL(_NSYM)

#define SC_UNDO LCTL(DE_Z)
#define SC_REDO LCTL(DE_Y)
#define SC_CUT LCTL(DE_X)
#define SC_COPY LCTL(DE_C)
#define SC_PSTE LCTL(DE_V)
#define SC_SPST LSFT(KC_INS)

// #define _________________________
#define ___L_THUMB_QWERTY________ TH_ESC, TH_BSPC, TH_TAB
#define ___R_THUMB_QWERTY________ TH_ENT, TH_SPC,  FUN_TAB
// #define ___________________________________________
#define ___L_TOP__SYMBOL___________________________ DE_GRV,  DE_LABK, DE_RABK, DE_AT,   DE_PERC
#define ___L_HOME_SYMBOL___________________________ DE_EXLM, DE_MINS, DE_PLUS, DE_EQL,  DE_HASH
#define ___L_BOT__SYMBOL___________________________ DE_EURO, DE_SLSH, DE_ASTR, DE_BSLS, DE_UNDS
#define ___R_TOP__SYMBOL___________________________ DE_AMPR, DE_CIRC, DE_LBRC, DE_RBRC, DE_DEG
#define ___R_HOME_SYMBOL___________________________ DE_PIPE, DE_COLN, DE_LPRN, DE_RPRN, DE_QUES
#define ___R_BOT__SYMBOL___________________________ DE_TILD, DE_DLR,  DE_LCBR, DE_RCBR, DE_SECT
#define ___L_NUMROW________________________________ DE_1,    DE_2,    DE_3,    DE_4,    DE_5
#define ___R_NUMROW________________________________ DE_6,    DE_7,    DE_8,    DE_9,    DE_0
#define ___L_MODROW________________________________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______
#define ___R_MODROW________________________________ _______, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI
#define ___L_BOT__NAV______________________________ SC_UNDO, SC_CUT,  SC_COPY, SC_PSTE, SC_SPST
#define ___R_TOP__NAV______________________________ KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______
#define ___R_HOME_NAV______________________________ KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
#define ___L_TOP__QWERTY___________________________ DE_Q,    DE_W,    DE_E,    DE_R,    DE_T
#define ___L_HOME_QWERTY___________________________ HB_A,    HB_S,    HB_D,    HB_F,    DE_G
#define ___L_BOT__QWERTY___________________________ DE_Z,    HB_X,    DE_C,    DE_V,    DE_B
#define ___R_TOP__QWERTY___________________________ DE_Y,    DE_U,    DE_I,    DE_O,    DE_P
#define ___R_HOME_QWERTY___________________________ DE_H,    HB_J,    HB_K,    HB_L,    HB_QUOT
#define ___R_BOT__QWERTY___________________________ DE_N,    DE_M,    DE_COMM, HB_DOT,  U_SLSH
#define ___L_TOP__MOUSE____________________________ KC_WH_L, KC_WH_U, KC_MS_U, KC_WH_D, KC_WH_R
#define ___L_HOME_MOUSE____________________________ _______, KC_MS_L, KC_MS_D, KC_MS_R, _______
#define ___L_BOT__MOUSE____________________________ _______, KC_BTN2, KC_BTN3, KC_BTN1, _______
#define ___L_FUNROW________________________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___R_FUNROW________________________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
