#pragma once

#include QMK_KEYBOARD_H

#include "keycodes.h"

#define _________________________
#define ___L_THUMB_QWERTY________ TH_ESC, TH_BSPC, TH_TAB
#define ___R_THUMB_QWERTY________ TH_ENT, TH_SPC,  FUN_TAB

#define ___________________________________________
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
#define ___R_BOT__QWERTY___________________________ DE_N,    DE_M,    TD_COMM, HB_DOT,  U_SLSH
#define ___L_TOP__MOUSE____________________________ KC_WH_L, KC_WH_U, KC_MS_U, KC_WH_D, KC_WH_R
#define ___L_HOME_MOUSE____________________________ _______, KC_MS_L, KC_MS_D, KC_MS_R, _______
#define ___L_BOT__MOUSE____________________________ _______, KC_BTN2, KC_BTN3, KC_BTN1, _______
#define ___L_FUNROW________________________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ___R_FUNROW________________________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
