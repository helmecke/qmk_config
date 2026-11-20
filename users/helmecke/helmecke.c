#include "helmecke.h"

// Matrix scan

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
    matrix_scan_keymap();
}

// Tap-hold

#ifdef CHORDAL_HOLD
// The Kyria rev2 matrix is 8x8: rows 0-3 are the left half, rows 4-7 the right
// half, and rows 3 and 7 hold the thumb clusters. A '*' handedness exempts a
// key from the opposite-hands rule: thumbs are pressed by either hand, and X
// and dot double as the AltGr keys, whose chords with the neighbouring letters
// have to stay chords.
char chordal_hold_handedness(keypos_t key) {
    if (key.row == 3 || key.row == 7) {
        return '*'; // thumb clusters
    }
    if ((key.row == 2 && key.col == 5) || (key.row == 6 && key.col == 5)) {
        return '*'; // HB_X and HB_DOT, the AltGr mod-taps
    }
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}
#endif // CHORDAL_HOLD

#ifdef PERMISSIVE_HOLD_PER_KEY
// Only the mod-taps resolve a nested tap as a hold before the tapping term.
// The thumb layer-taps are left out on purpose: they are used as ordinary taps
// in the middle of typing, and resolving them as holds would drop a following
// key onto the layer.
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HB_A:
        case HB_S:
        case HB_D:
        case HB_F:
        case HB_J:
        case HB_K:
        case HB_L:
        case HB_QUOT:
        case HB_X:
        case HB_DOT:
            return true;
        default:
            return false;
    }
}
#endif // PERMISSIVE_HOLD_PER_KEY

#ifdef OS_DETECTION_ENABLE
// Host settings that have actually been applied to the host-facing features.
// QMK detects the OS asynchronously and debounces the result; this value only
// changes in the debounced process_detected_host_os_user() callback, so
// modifier swapping, punctuation and display reporting all read the same view.
// OS_UNSURE means "nothing applied yet" and keeps normal typing available with
// non-Apple settings. The peripheral half never applies host settings and
// reports the synchronized detected value instead (see helmecke_os()).
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

#ifdef GERMAN_US_ENABLE
    // German-US punctuation is the only local handler. It reports TRUE when the
    // event was consumed after being emitted and FALSE when it was consumed
    // without reaching the action layer; anything else continues to QMK.
    return process_german_us(keycode, record) != PROCESS_RECORD_RETURN_FALSE;
#endif /* ifdef GERMAN_US_ENABLE */

    return true;
}
