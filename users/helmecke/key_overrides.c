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
const key_override_t adia_key_override = ko_make_basic(MOD_MASK_SA, HB_A, DE_ADIA);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
  &del_key_override,
  &adia_key_override,
  NULL // Null terminate the array of overrides!
};
