#pragma once

#include "layers.h"
#include "keymap_german.h"

// Custom keycodes
enum {
    // clang-format off
    CUSTOM_KEYCODE_START = SAFE_RANGE,
    U_SLSH,
    U_LBRC,
    U_RBRC,
    U_SZ,
    CUSTOM_KEYCODE_END
    // clang-format on
};

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
// QMK mod-tap stores its tap keycode in the low eight bits, so these must not
// wrap a custom (>= SAFE_RANGE) keycode: the tap key would be truncated and a
// bogus character would leak. The German quote output is produced by the
// explicit tap interception in features/german_us.c instead.
#define HB_QUOT RGUI_T(KC_QUOT)
#define HB_DOT ALGR_T(DE_DOT)

// Left-thumb
#define TH_ESC LT(_MOUSE, KC_ESC)
#define TH_BSPC LT(_SYM, KC_BSPC)
#define TH_TAB LT(_NAV, KC_TAB)

// Right-thumb
#define TH_ENT LT(_MOUSE, KC_ENT)
#define TH_SPC LT(_NUM, KC_SPC)
#define FUN_TAB LT(_FUN, KC_TAB)

#define U_RST QK_BOOT
#define U_DBG DB_TOGG

#define SC_UNDO LCTL(DE_Z)
#define SC_REDO LCTL(DE_Y)
#define SC_CUT LCTL(DE_X)
#define SC_COPY LCTL(DE_C)
#define SC_PSTE LCTL(DE_V)
#define SC_SPST LSFT(KC_INS)
