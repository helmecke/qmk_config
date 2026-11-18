#pragma once

// Registration tables for features that QMK resolves through keymap
// introspection: tap dance actions and key overrides.
//
// keymap_introspection.c compiles the keymap translation unit and takes
// ARRAY_SIZE() of these tables, so the complete array definitions have to be
// visible from the keymap. Include this header from a keymap after helmecke.h.
// The callbacks and override definitions stay in features/ and are compiled
// separately, so the tables are still defined exactly once.
//
// Both tables are feature-gated: a board that does not enable the feature does
// not include it and does not depend on the corresponding core tables.

#include QMK_KEYBOARD_H

#include "keycodes.h"

#ifdef TAP_DANCE_ENABLE
#    include "../features/tap_dance.h"

tap_dance_action_t tap_dance_actions[] = {
    [COM_LEA] = ACTION_TAP_DANCE_FN(td_comm),
};
#endif // TAP_DANCE_ENABLE

#ifdef KEY_OVERRIDE_ENABLE
#    include "../features/key_override.h"

// Arrays of override pointers are terminated by their size in current QMK;
// the historical trailing NULL sentinel is not needed any more.
const key_override_t *const key_overrides[] = {
    &del_key_override,
    &adia_key_override,
    &ss_key_override,
    &udia_key_override,
    &odia_key_override,
    &exlm_key_override,
    &ques_key_override,
};
#endif // KEY_OVERRIDE_ENABLE
