#include QMK_KEYBOARD_H

#include "custom_leader_func.h"

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case DE_W:
            dprint("Leader W...\n");
            tap_code16(DE_MINS);
            return NULL;
        default:
            return NULL;
    }
    return NULL;
}
