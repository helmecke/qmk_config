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

#ifndef BOOTMAGIC_ENABLE
/* Top left key on left half */
#undef BOOTMAGIC_LITE_ROW
#undef BOOTMAGIC_LITE_COLUMN
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 1
/* Top right key on right half */
#undef BOOTMAGIC_LITE_ROW_RIGHT
#undef BOOTMAGIC_LITE_COLUMN_RIGHT
#define BOOTMAGIC_LITE_ROW_RIGHT    4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 4
#endif

#define LAYOUT_helmecke(\
       K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,\
       K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,\
       K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,\
                     K30,   K31,   K32,          K33,   K34,   K35\
)\
LAYOUT_split_3x6_3(\
KC_NO, K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09,   KC_NO,\
KC_NO, K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19,   KC_NO,\
KC_NO, K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29,   KC_NO,\
                     K30,   K31,   K32,          K33,   K34,   K35\
)
