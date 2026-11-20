/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
#define SPLIT_USB_DETECT
#define NO_USB_STARTUP_CHECK
#define SPLIT_USB_TIMEOUT 4000

// Synchronize the detected host OS from the USB half to the peripheral half.
// The applied OS is owned by process_detected_host_os_user() in
// users/helmecke/helmecke.c.
#define SPLIT_DETECTED_OS_ENABLE

// The only display is on the left half, so it also renders the status screen
// when the right half is the USB half. Layer and host lock state come from the
// master and have to be synchronized for that screen to be correct.
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

// Tap-hold: a home-row mod-tap overlapping a key of the other hand may settle
// as a hold, and a nested tap (press and release the other key before the
// mod-tap) settles the chord as held on that release, so capitals no longer
// depend on the timing. Chordal Hold is what keeps same-hand rolls as taps; the
// handedness comes from chordal_hold_handedness() in users/helmecke/helmecke.c.
#define CHORDAL_HOLD
// Permissive Hold is limited per key: the home-row mod-taps (plus the AltGr
// taps X and dot) resolve early, while the thumb layer-taps keep waiting for
// the tapping term. A quick thumb-then-key sequence therefore stays a tap of
// the thumb (Space/Tab/Enter) instead of dropping into the layer.
#define PERMISSIVE_HOLD_PER_KEY

// Caps Word: both left and right Shift held, then released, turn it on. This
// works with the D/K home-row Shift mod-taps (hold them past the preserved
// 200 ms tapping term) and with explicit Shift keys on any layer. Current QMK
// no longer ships the Command feature, which used the same Shift pair, so there
// is no conflict to resolve.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// An explicit idle timeout; CAPS_WORD_INVERT_ON_SHIFT stays disabled so Shift
// always ends the word.
#define CAPS_WORD_IDLE_TIMEOUT 5000

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

#ifdef ENCODER_ENABLE
  // EC11K encoders have a different resolution than other EC11 encoders.
  // When using the default resolution of 4, if you notice your encoder skipping
  // every other tick, lower the resolution to 2.
  #define ENCODER_RESOLUTION 2
  // Also, flip direction
  #define ENCODER_DIRECTION_FLIP
#endif

// Only the left half has a display. The Kyria info.json enables OLED state sync
// (split.transport.sync.oled), which is generated into info_config.h as
// SPLIT_OLED_ENABLE. That sync sends the master's on/off state to the
// peripheral half; when the USB half has no display its state is always "off",
// which turns the left display off when the right half is the USB half. This
// file is included after info_config.h, so undo the sync here. Each half then
// drives its own display and timeout, and because the master's matrix state is
// synced, activity on either half still wakes the display.
#ifdef SPLIT_OLED_ENABLE
#    undef SPLIT_OLED_ENABLE
#endif

#ifdef POINTING_DEVICE_ENABLE
#define CIRQUE_PINNACLE_CURVED_OVERLAY

#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#endif
