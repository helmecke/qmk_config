/*
Copyright 2022 Jakob Helmecke @helmecke

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "tap_dances.h"
#include "layers.h"
#include "features/features.h"
#include "keymap_german.h"

// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
td_state_t cur_dance(qk_tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance(qk_tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted) {
            if (!state->pressed)
                return TD_SINGLE_TAP;
            else
                return TD_SINGLE_HOLD;
        } else {
            if (!state->pressed)
                return TD_SINGLE_TAP;
            else
                return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
    // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
    // with single tap.
        if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (!state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for each tap dance.
static td_tap_t mins_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t lead_state = { .is_press_action = true, .state = TD_NONE };

void mins_finished(qk_tap_dance_state_t* state, void* user_data) {
    mins_state.state = cur_dance(state);
    switch (mins_state.state) {
        case TD_SINGLE_TAP: register_code(KC_MINS); break;
        case TD_SINGLE_HOLD: register_code(KC_SLSH); break;
        case TD_DOUBLE_TAP: register_code(KC_MINS); register_code(KC_MINS); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_MINS); register_code(KC_MINS); break;
        default: tap_code(KC_MINS); register_code(KC_MINS); break;
    }
}

void mins_reset(qk_tap_dance_state_t* state, void* user_data) {
    switch (mins_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_MINS); break;
        case TD_SINGLE_HOLD: unregister_code(KC_SLSH); break;
        case TD_DOUBLE_TAP: unregister_code(KC_MINS); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_MINS); break;
        default: unregister_code(KC_MINS); break;
    }
    mins_state.state = TD_NONE;
}

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >=2) {
        // Reset the keyboard if you tap the key more than three times
        reset_keyboard();
        reset_tap_dance(state);
    }
};

void lead_finished(qk_tap_dance_state_t* state, void* user_data) {
    lead_state.state = cur_dance(state);
    switch (lead_state.state) {
        case TD_SINGLE_HOLD: layer_on(_FUN); break;
        default: start_leading(); break;
    }
}

void lead_reset(qk_tap_dance_state_t* state, void* user_data) {
    switch (lead_state.state) {
        case TD_DOUBLE_TAP: register_code(KC_MINS); register_code(KC_MINS); break;
        default: break;
    }
    lead_state.state = TD_NONE;
}

void lead(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >=2) {
        start_leading();
        reset_tap_dance(state);
    } else {
        tap_code(DE_COMM);
        reset_tap_dance(state);
    }
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
    [TD_MINS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mins_finished, mins_reset),
    [TD_LEAD] = ACTION_TAP_DANCE_FN(lead),
};
