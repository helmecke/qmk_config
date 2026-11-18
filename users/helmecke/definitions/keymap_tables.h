#pragma once

// Registration table for key overrides. QMK resolves overrides through keymap
// introspection: keymap_introspection.c compiles the keymap translation unit
// and takes ARRAY_SIZE() of the table, so the complete array definition has to
// be visible from the keymap. Include this header from a keymap after
// helmecke.h. The override definitions and callbacks stay in features/ and are
// compiled separately, so each object is still defined exactly once.
//
// The table is feature-gated: a board that does not enable key overrides does
// not include it and does not depend on the corresponding core table.

#include QMK_KEYBOARD_H

#include "keycodes.h"

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
