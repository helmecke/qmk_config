#pragma once

#include QMK_KEYBOARD_H

// Key override definitions. The registered table lives in
// definitions/keymap_tables.h so that QMK keymap introspection can see the
// complete array; the override definitions themselves stay next to the
// callbacks that implement them.
extern const key_override_t del_key_override;
extern const key_override_t adia_key_override;
extern const key_override_t ss_key_override;
extern const key_override_t udia_key_override;
extern const key_override_t odia_key_override;
extern const key_override_t exlm_key_override;
extern const key_override_t ques_key_override;
