#pragma once

#include "layers.h"
#include "keymap_german.h"

#ifdef TAP_DANCE_ENABLE
// Tap Dance Declarations
enum {
    // clang-format off
    TD_CODE_START,
    COM_LEA,
    TD_CODE_END
    // clang-format on
};

#    define TD_COMM TD(COM_LEA)
#else
#    define TD_COMM DE_COMM
#endif

// Custom keycodes
enum {
    // clang-format off
    CUSTOM_KEYCODE_START = SAFE_RANGE,
    STORE_SETUPS,
    PRINT_SETUPS,
    TG_MAC,
    TG_WIN,
    U_QUOT,
    U_SCLN,
    U_SLSH,
    U_LBRC,
    U_RBRC,
    U_PLUS,
    U_OS,
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

#define U_RST QK_BOOT
#define U_DBG DB_TOGG

#if defined(OS_DETECTION_ENABLE) && defined(OS_DETECTION_DEBUG_ENABLE)
#    define U_SS STORE_SETUPS
#    define U_PS PRINT_SETUPS
#else
#    define U_SS _______
#    define U_PS _______
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

uint16_t extract_tapping_keycode(uint16_t keycode);
