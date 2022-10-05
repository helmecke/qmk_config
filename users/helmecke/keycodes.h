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
#define HB_R LALT_T(DE_R)
#define HC_S LSFT_T(DE_S)
#define HB_T LCTL_T(DE_T)

// Right-hand home row mods
#define HB_J RCTL_T(DE_J)
#define HB_K RSFT_T(DE_K)
#define HB_L LALT_T(DE_L)
#define HB_QUOT RGUI_T(U_QUOT)
#define HB_DOT ALGR_T(DE_DOT)
#define HB_N RCTL_T(DE_N)
#define HB_E RSFT_T(DE_E)
#define HB_I LALT_T(DE_I)
#define HB_O RGUI_T(DE_O)

// Left-thumb
#define TH_ESC LGUI_T(KC_ESC)
#define TH_BSPC LT(_SYM, KC_BSPC)
#define TH_REP LT(_NAV, REPEAT)

// Right-thumb
#define TH_ENT LT(_MOUSE, KC_ENT)
#define TH_SPC LT(_NUM, KC_SPC)
#define TH_TAB LT(_FUN, KC_TAB)

#ifdef TAP_DANCE_ENABLE
    #define U_RST TD(TD_RESET)
    #define U_DOT TD(TD_DOT)
    #define U_MINS TD(TD_MINS)
    #define U_LEAD TD(TD_LEAD)
#else
    #define U_RST QK_BOOT
    #define U_DOT _______
    #define U_MINS _______
    #define U_LEAD LEADER
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

#define COLEMAK DF(_COLEMAK)
#define QWERTY DF(_QWERTY)

#define ___L_TOP__COLEMAK___ DE_Q, DE_W, DE_F, DE_P, DE_G
#define ___L_HOME_COLEMAK___ HB_A, HB_R, HC_S, HB_T, DE_D
#define ___L_BOT__COLEMAK___ DE_Z, HB_X, DE_C, DE_V, DE_B
#define ___R_TOP__COLEMAK___ DE_J, DE_L, DE_U, DE_Y, U_QUOT
#define ___R_HOME_COLEMAK___ DE_H, HB_N, HB_E, HB_I, HB_O
#define ___R_BOT__COLEMAK___ DE_K, DE_M, DE_COMM, HB_DOT, DE_MINS
#define ___L_THUMB___ TH_ESC, TH_BSPC, TH_REP
#define ___R_THUMB___ TH_ENT, TH_SPC, TH_TAB
#define ___L_TOP__SYMBOL___ DE_GRV, DE_LABK, DE_RABK, DE_AT, DE_DEG
#define ___L_HOME_SYMBOL___ DE_EXLM, DE_MINS, DE_PLUS, DE_EQL, DE_HASH
#define ___L_BOT__SYMBOL___ DE_QUES, DE_SLSH, DE_ASTR, DE_BSLS, DE_SECT
#define ___R_TOP__SYMBOL___ DE_AMPR, DE_CIRC, DE_LCBR, DE_RCBR, DE_PERC
#define ___R_HOME_SYMBOL___ DE_PIPE, DE_COLN, DE_LPRN, DE_RPRN, DE_EURO
#define ___R_BOT__SYMBOL___ DE_TILD, DE_DLR, DE_LBRC, DE_RBRC, DE_UNDS
#define ___L_NUMROW________ DE_1, DE_2, DE_3, DE_4, DE_5
#define ___R_NUMROW________ DE_6, DE_7, DE_8, DE_9, DE_0
#define ___L_MODROW________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______
#define ___R_MODROW________ _______, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI
#define ___R_TOP__NAV______ KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______
#define ___R_HOME_NAV______ KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
