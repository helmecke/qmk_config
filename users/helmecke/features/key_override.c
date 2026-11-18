#include "helmecke.h"

#include "key_override.h"

#ifdef CAPS_WORD_ENABLE
#    include "caps_word.h"
#endif // CAPS_WORD_ENABLE

const key_override_t del_key_override = ko_make_basic(MOD_MASK_SA, TH_BSPC, KC_DEL);
const key_override_t adia_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_A, DE_ADIA);
const key_override_t udia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_U, DE_UDIA);
const key_override_t odia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_O, DE_ODIA);
const key_override_t exlm_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_DOT, DE_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_BIT(KC_RALT), TD_COMM, DE_QUES);

#ifdef CAPS_WORD_ENABLE
// AltGr+S types ß. The capital form of ß is "SS", so while Caps Word is active
// this override emits two S keystrokes instead of registering the replacement:
// the Caps Word weak Shift would turn ß into "?" and the held AltGr would alter
// the synthetic output otherwise. The override machinery already suppresses
// AltGr and restores the modifier state when the override is deactivated.
static bool ss_in_caps_word = false;

static bool ss_key_override_action(bool activated, void *context) {
    if (!activated) {
        bool handled    = ss_in_caps_word;
        ss_in_caps_word = false;
        return !handled;
    }

    if (is_caps_word_on()) {
        ss_in_caps_word = true;
        tap_code16(DE_S);
        tap_code16(DE_S);
        return false;
    }

    ss_in_caps_word = false;
    return true;
}

const key_override_t ss_key_override = {
    .trigger           = HB_S,
    .trigger_mods      = MOD_BIT(KC_RALT),
    .layers            = ~0,
    .negative_mod_mask = 0,
    .suppressed_mods   = MOD_BIT(KC_RALT),
    .replacement       = DE_SS,
    .options           = ko_options_default,
    .custom_action     = ss_key_override_action,
    .context           = NULL,
    .enabled           = NULL,
};
#else
const key_override_t ss_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_S, DE_SS);
#endif // CAPS_WORD_ENABLE

// The registered override table is defined in definitions/keymap_tables.h so
// that QMK keymap introspection can see the complete array from the keymap
// translation unit.
