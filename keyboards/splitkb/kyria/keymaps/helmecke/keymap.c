#include QMK_KEYBOARD_H

#include "helmecke.h"
#include "definitions/keymap_tables.h"

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_wrapper(
      DE_ADIA, ___L_TOP__QWERTY___________________________,                                            ___R_TOP__QWERTY___________________________, DE_UDIA,
      U_LBRC,  ___L_HOME_QWERTY___________________________,                                            ___R_HOME_QWERTY___________________________, U_RBRC,
      U_SZ,    ___L_BOT__QWERTY___________________________, _______, _______,        _______, _______, ___R_BOT__QWERTY___________________________, DE_ODIA,
                             KC_MUTE, MO(_ADJUST), ___L_THUMB_QWERTY________,        ___R_THUMB_QWERTY________, MO(_ADJUST), KC_MPLY
    ),

    [_NAV] = LAYOUT_wrapper(
      _______, _______, _______, _______, _______, _______,                                            ___R_TOP__NAV______________________________, _______,
      _______, ___L_MODROW________________________________,                                            ___R_HOME_NAV______________________________, _______,
      _______, ___L_BOT__NAV______________________________, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT_wrapper(
      _______, ___L_NUMROW________________________________,                                            ___R_NUMROW________________________________, _______,
      _______, ___L_MODROW________________________________,                                            ___R_MODROW________________________________, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, DE_COMM, DE_DOT,  _______, _______,
                                 _______, _______, _______, _______, _______,        _______, _______, U_RST,   _______, _______
    ),

    [_SYM] = LAYOUT_wrapper(
      _______, ___L_TOP__SYMBOL___________________________,                                            ___R_TOP__SYMBOL___________________________, _______,
      _______, ___L_HOME_SYMBOL___________________________,                                            ___R_HOME_SYMBOL___________________________, _______,
      _______, ___L_BOT__SYMBOL___________________________, _______, _______,        _______, _______, ___R_BOT__SYMBOL___________________________, _______,
                                 _______, _______, U_RST  , _______, _______,        _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT_wrapper(
      _______, ___L_TOP__MOUSE____________________________,                                            _______, _______, _______, _______, _______, _______,
      _______, ___L_HOME_MOUSE____________________________,                                            ___R_MODROW________________________________, _______,
      _______, ___L_BOT__MOUSE____________________________, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
    ),

    [_FUN] = LAYOUT_wrapper(
      _______, ___L_FUNROW________________________________,                                            ___R_FUNROW________________________________, _______,
      _______, ___L_MODROW________________________________,                                            ___R_MODROW________________________________, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_wrapper(
      _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                            UG_TOGG, UG_SATU, UG_HUEU, UG_VALU,  UG_NEXT, _______,
      _______, U_DBG  , _______, _______, _______, _______, _______, _______,         _______, _______, _______, UG_SATD, UG_HUED, UG_VALD, UG_PREV, _______,
                                 _______, _______, _______,_______, _______,         _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT_wrapper(
//       _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______
//     ),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_NAV] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_NUM] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_SYM] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_MOUSE] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_FUN] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
    [_ADJUST] = { { KC_VOLD, KC_VOLU }, { KC_MPRV, KC_MNXT } },
};
// clang-format on
#endif
/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_macos_logo(void) {
    static const char PROGMEM qmk_logo[] = {149, 150, 10, 181, 182, 0};

    oled_write_P(qmk_logo, false);
}

static void render_windows_logo(void) {
    static const char PROGMEM qmk_logo[] = {151, 152, 10, 183, 184, 0};

    oled_write_P(qmk_logo, false);
}

static void render_linux_logo(void) {
    static const char PROGMEM qmk_logo[] = {153, 154, 10, 185, 186, 0};

    oled_write_P(qmk_logo, false);
}

static void render_unknown_logo(void) {
    // Host OS detection is a USB fingerprint, so an unknown host is displayed
    // as such instead of being reported as one of the known systems.
    static const char PROGMEM qmk_logo[] = {'?', '\n', '?', 0};

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    // The status screen is rendered by whichever half owns a display. Only the
    // left half has one, so this also shows layer and lock state when the right
    // half is the USB half; those fields are synced with
    // SPLIT_LAYER_STATE_ENABLE and SPLIT_LED_STATE_ENABLE.
    switch (helmecke_os()) {
        case OS_UNSURE:
            render_unknown_logo();
            break;
        case OS_LINUX:
            render_linux_logo();
            break;
        case OS_WINDOWS:
            render_windows_logo();
            break;
        case OS_MACOS:
            render_macos_logo();
            break;
        case OS_IOS:
            render_macos_logo();
            break;
    }

    oled_write_P(PSTR("\n\nKyria rev2.1\n"), false);

    // Caps Word state comes from the core feature. It is a host-facing state on
    // the USB half; the peripheral has no copy, so the line stays blank there
    // instead of showing a stale value. The line is kept when the feature is
    // not compiled in so the layout below stays in place.
#ifdef CAPS_WORD_ENABLE
    oled_write_P((is_keyboard_master() && is_caps_word_on()) ? PSTR("CapsWord: on\n") : PSTR("\n"), false);
#else
    oled_write_P(PSTR("\n"), false);
#endif // CAPS_WORD_ENABLE

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("Number\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbol\n"), false);
            break;
        case _FUN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status, synced to the peripheral half
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

    return false;
}
#endif
