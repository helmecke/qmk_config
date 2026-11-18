#include "helmecke.h"

// Matrix scan

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

#ifdef OS_DETECTION_ENABLE
// Host settings that have actually been applied to the host-facing features.
// QMK detects the OS asynchronously and debounces the result; this value only
// changes in the debounced process_detected_host_os_user() callback, so
// modifier swapping, punctuation, Unicode mode and display reporting all read
// the same view. OS_UNSURE means "nothing applied yet" and keeps normal typing
// available with non-Apple settings. The peripheral half never applies host
// settings and reports the synchronized detected value instead (see
// helmecke_os()).
static os_variant_t applied_os = OS_UNSURE;

os_variant_t helmecke_os(void) {
    if (!is_keyboard_master()) {
        // The peripheral half receives the detected OS over the split
        // transport, but it never applies host settings (it has no USB
        // connection to the host), so its display reports the synchronized
        // detected value instead of the applied one.
        return detected_host_os();
    }
    return applied_os;
}

bool helmecke_os_is_apple(void) {
    const os_variant_t os = helmecke_os();

    return os == OS_MACOS || os == OS_IOS;
}

bool process_detected_host_os_user(os_variant_t os) {
    applied_os = os;

    // Only the USB-connected half talks to the host. The peripheral half still
    // receives the detected value through SPLIT_DETECTED_OS_ENABLE so that its
    // display reports the same OS, but it must not persist host settings.
    if (is_keyboard_master()) {
        const bool is_apple                          = (os == OS_MACOS) || (os == OS_IOS);
        keymap_config.swap_lctl_lgui = keymap_config.swap_rctl_rgui = is_apple;

#    ifdef UNICODE_COMMON_ENABLE
        uint8_t mode;
        switch (os) {
            case OS_LINUX:
                mode = UNICODE_MODE_LINUX;
                break;
            case OS_MACOS:
            case OS_IOS:
                mode = UNICODE_MODE_MACOS;
                break;
            default:
                // Windows and an unknown host keep WinCompose, the existing
                // Windows input method, as the safe non-Apple default.
                mode = UNICODE_MODE_WINCOMPOSE;
                break;
        }
        if (mode != get_unicode_input_mode()) {
            set_unicode_input_mode(mode);
        }
#    endif // UNICODE_COMMON_ENABLE
    }

    switch (os) {
        case OS_UNSURE:
            dprintf("Detected OS: unknown\n");
            break;
        case OS_LINUX:
            dprintf("Detected OS: Linux\n");
            break;
        case OS_WINDOWS:
            dprintf("Detected OS: Windows\n");
            break;
        case OS_MACOS:
            dprintf("Detected OS: macOS\n");
            break;
        case OS_IOS:
            dprintf("Detected OS: iOS\n");
            break;
    }

    return true;
}
#endif // OS_DETECTION_ENABLE

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
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
