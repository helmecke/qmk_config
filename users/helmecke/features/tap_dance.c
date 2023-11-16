#include QMK_KEYBOARD_H

#include "tap_dance.h"
#include "../definitions/layers.h"
#include "keymap_german.h"

static td_tap_t tap_state = {.state = TD_NONE};

__attribute__((weak)) td_state_t dance_state(tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

bool is_shifted(void) {
    return get_mods() & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
}

void td_comm(tap_dance_state_t* state, void* user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(DE_COMM);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(DE_COMM);
            tap_code(DE_COMM);
            break;
        case TD_DOUBLE_TAP:
#ifdef CUSTOM_LEADER_ENABLE
            if (!is_shifted()) {
                leader_start();
            } else {
                tap_code(DE_COMM);
                tap_code(DE_COMM);
            }
#endif /* ifdef CUSTOM_LEADER_ENABLE */
#ifndef CUSTOM_LEADER_ENABLE
            tap_code(DE_COMM);
            tap_code(DE_COMM);
#endif /* ifndef CUSTOM_LEADER_ENABLE */
            break;
        case TD_TRIPLE_TAP:
            tap_code(DE_COMM);
            tap_code(DE_COMM);
            tap_code(DE_COMM);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(KC_END);
            tap_code(DE_COMM);
            break;
        default:
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [COM_LEA] = ACTION_TAP_DANCE_FN(td_comm),
};
