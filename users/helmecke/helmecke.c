#include "helmecke.h"

// Matrix scan

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

#ifdef OS_DETECTION_ENABLE
os_variant_t os_type;

uint32_t startup_exec(uint32_t trigger_time, void *cb_arg) {
    if (is_keyboard_master()) {
        os_type = detected_host_os();
        if (os_type) {
            bool is_mac                  = (os_type == OS_MACOS) || (os_type == OS_IOS);
            keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = is_mac;
#    ifdef UNICODE_COMMON_ENABLE
            uint8_t mode = is_mac ? UNICODE_MODE_MACOS : UNICODE_MODE_WINCOMPOSE;
            if (mode != get_unicode_input_mode()) {
                set_unicode_input_mode(mode);
            }
#    endif
            switch (os_type) {
                case OS_UNSURE:
                    xprintf("unknown OS Detected\n");
                    break;
                case OS_LINUX:
                    xprintf("Linux Detected\n");
                    break;
                case OS_WINDOWS:
                    xprintf("Windows Detected\n");
                    break;
                case OS_MACOS:
                    xprintf("MacOS Detected\n");
                    break;
                case OS_IOS:
                    xprintf("iOS Detected\n");
                    break;
            }
        }
    }

    return os_type ? 0 : 500;
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;

#    ifdef OS_DETECTION_ENABLE
    defer_exec(100, startup_exec, NULL);
#    endif
#endif /* ifdef CONSOLE_ENABLE */
}

// Process record

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef KEYLOGGER_ENABLE
    // clang-format off
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %1d, time: %5u, int: %1d, count: %u, layer: %2u, mods: 0x%02X, os_mods: 0x%02X\n",
        keycode,
        record->event.key.col,
        record->event.key.row,
        record->event.pressed,
        record->event.time,
        record->tap.interrupted,
        record->tap.count,
        get_highest_layer(layer_state),
        get_mods(),
        get_oneshot_mods()
    );
    // clang-format on
#endif

#ifdef CUSTOM_LEADER_ENABLE
    switch (process_leader(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    }
        // if (!process_leader(keycode, record)) {
        //     return_state = false;
        // }
#endif

#ifdef GERMAN_US_ENABLE
    switch (process_german_us(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif /* ifdef GERMAN_US_ENABLE */

    return true;
}
