#include "helmecke.h"

const key_override_t del_key_override = ko_make_basic(MOD_MASK_SA, TH_BSPC, KC_DEL);
const key_override_t adia_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_A, DE_ADIA);
const key_override_t ss_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_S, DE_SS);
const key_override_t udia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_U, DE_UDIA);
const key_override_t odia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_O, DE_ODIA);
const key_override_t exlm_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_DOT, DE_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_BIT(KC_RALT), TD_COMM, DE_QUES);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
  &del_key_override,
  &adia_key_override,
  &ss_key_override,
  &udia_key_override,
  &odia_key_override,
  &exlm_key_override,
  &ques_key_override,
  NULL // Null terminate the array of overrides!
};
