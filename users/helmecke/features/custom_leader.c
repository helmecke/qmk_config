#include "custom_leader.h"

#include <string.h>

#ifndef LEADER_ESC_KEY
#    define LEADER_ESC_KEY KC_ESC
#endif

static bool          leading     = false;
static leader_func_t leader_func = NULL;

// The entry point for leader sequenc functions
__attribute__((weak)) void *leader_start_func(uint16_t keycode) {
    return NULL;
}

// Check to see if we are leading
bool leader_sequence_active(void) {
    return leading;
}
// Start leader sequence
void leader_start(void) {
    if (leading) {
        leader_end();
        return;
    }
    leading     = true;
    leader_func = leader_start_func;
}
// Stop leader sequence
void leader_end(void) {
    leading     = false;
    leader_func = NULL;
}

// Process keycode for leader sequences
process_record_result_t process_leader(uint16_t keycode, const keyrecord_t *record) {
    if (record != NULL && !record->event.pressed) {
        return PROCESS_RECORD_CONTINUE;
    }

    if (leading) {
#ifndef NO_ACTION_TAPPING
        // Get the base keycode of a mod or layer tap key
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
                // Earlier return if this has not been considered tapped yet
                if (record->tap.count == 0) return PROCESS_RECORD_CONTINUE;
                keycode = keycode & 0xFF;
                break;
            default:
                break;
        }
#endif
        // let through anything above that's normal keyboard keycode or a mod
        if (keycode > QK_MODS_MAX || IS_MODIFIER_KEYCODE(keycode)) {
            switch (keycode) {
                // special keycodes used in leader funcs
                case LEADER_ESC_KEY:
                    // early exit if the esc key was hit
                    if (record->event.pressed) {
                        leader_end();
                    }
                    return PROCESS_RECORD_RETURN_FALSE;
                default:
                    return PROCESS_RECORD_RETURN_TRUE;
            }
        }
        if (record->event.pressed) {
            // update the leader function
            leader_func = leader_func(keycode);
            if (leader_func == NULL) {
                leader_end();
            }
        }
        if (keycode == KC_SPC) {
            return PROCESS_RECORD_RETURN_TRUE;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }

    return PROCESS_RECORD_CONTINUE;
}
