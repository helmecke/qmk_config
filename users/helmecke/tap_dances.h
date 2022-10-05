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

#pragma once

// Declare available Tap-Dance states
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_DOUBLE_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_HOLD,
    TD_UNKNOWN,
} td_state_t;

// Tap-Dance struct
typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance Declarations
enum {
    TD_RESET,
    TD_MINS,
    TD_LEAD,
    TD_REPEAT,
};
