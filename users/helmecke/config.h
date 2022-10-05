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

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Configure the global combo term (default: 50ms)
#define COMBO_TERM 60

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Mouse key speed and acceleration.
// Delay between pressing a movement key and cursor movement (default: 10)
#define MOUSEKEY_DELAY 5
// Time between cursor movements in milliseconds (default: 20)
#define MOUSEKEY_INTERVAL 13
// Maximum cursor speed at which acceleration stops (default: 10)
#define MOUSEKEY_MAX_SPEED 6
// Time until maximum cursor speed is reached (default: 30)
#define MOUSEKEY_TIME_TO_MAX 64
// Delay between pressing a wheel key and wheel movement (default: 10)
#define MOUSEKEY_WHEEL_DELAY 5
// Forces the keyboard to wait for a USB connection to be established before it starts up
// #define WAIT_FOR_USB
