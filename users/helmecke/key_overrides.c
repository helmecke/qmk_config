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

#include "helmecke.h"

const key_override_t del_key_override = ko_make_basic(MOD_MASK_SA, TH_BSPC, KC_DEL);
const key_override_t adia_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_A, DE_ADIA);
const key_override_t ss_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_S, DE_SS);
const key_override_t udia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_U, DE_UDIA);
const key_override_t odia_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_O, DE_ODIA);
const key_override_t exlm_key_override = ko_make_basic(MOD_BIT(KC_RALT), HB_DOT, DE_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_BIT(KC_RALT), DE_COMM, DE_QUES);

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
