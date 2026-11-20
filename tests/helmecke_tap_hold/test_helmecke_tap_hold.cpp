// Copyright 2026 Jakob Helmecke
// SPDX-License-Identifier: GPL-2.0-or-later

// Tap-hold integration: Chordal Hold's handedness rule and the per-key
// Permissive Hold exception, exercised through QMK's real event processing.
// The fixture uses the 4x10 test matrix and maps the Kyria rule onto it: rows
// 0-1 are the left hand, row 2 the right hand and row 3 the thumb cluster, so
// chordal_hold_handedness() takes its thumb branch on row 3 and its AltGr
// branch on (2,5). The positions are chosen to reach those branches, not to
// reproduce the board geometry.
//
// The roll case (release the mod-tap before the other key) stays a tap for both
// keys; that is QMK's documented boundary and the reason capitals use the
// nested order.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
#include "../../users/helmecke/definitions/keycodes.h"
#include "../../users/helmecke/definitions/layers.h"

char chordal_hold_handedness(keypos_t key);
}

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::InSequence;

namespace {

// Reports without a key, e.g. a modifier being registered or a key release,
// are interleaved with the key reports the individual tests assert on.
MATCHER(NoKeysReport, "is a keyboard report without keys") {
    for (uint8_t key : arg.keys) {
        if (key != 0) {
            return false;
        }
    }
    return true;
}

void allow_modifier_reports(TestDriver &driver) {
    EXPECT_CALL(driver, send_keyboard_mock(NoKeysReport())).Times(AnyNumber());
}

class TapHoldIntegration : public TestFixture {};

} // namespace

// The handedness rule on the test matrix: the left rows are 'L', the right row
// is 'R', the thumb row and the AltGr slot are exempt with '*'.
TEST_F(TapHoldIntegration, Handedness) {
    EXPECT_EQ(chordal_hold_handedness({.col = 0, .row = 0}), 'L');
    EXPECT_EQ(chordal_hold_handedness({.col = 9, .row = 1}), 'L');
    EXPECT_EQ(chordal_hold_handedness({.col = 0, .row = 2}), 'R');
    EXPECT_EQ(chordal_hold_handedness({.col = 5, .row = 2}), '*');
    EXPECT_EQ(chordal_hold_handedness({.col = 0, .row = 3}), '*');
    EXPECT_EQ(chordal_hold_handedness({.col = 9, .row = 3}), '*');
}

// A capital: hold the right home-row Shift, tap a left-hand letter nested, and
// release the letter first. Permissive Hold settles the chord as held on the
// letter's release, independently of the tapping term.
TEST_F(TapHoldIntegration, NestedTapSettlesShiftHold) {
    TestDriver driver;
    InSequence s;

    KeymapKey shift(0, 1, 2, HB_K);
    KeymapKey letter(0, 0, 0, DE_A);
    set_keymap({shift, letter});

    EXPECT_NO_REPORT(driver);
    shift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RSFT));
    EXPECT_REPORT(driver, (KC_RSFT, KC_A));
    EXPECT_REPORT(driver, (KC_RSFT));
    tap_key(letter);
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    shift.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// The counter-check: the same two keys rolled the other way (the mod-tap is
// released first) stay a tap for both keys. This is the documented boundary.
TEST_F(TapHoldIntegration, RollStaysATap) {
    TestDriver driver;
    InSequence s;

    KeymapKey shift(0, 1, 2, HB_K);
    KeymapKey letter(0, 1, 0, DE_U);
    set_keymap({shift, letter});

    EXPECT_NO_REPORT(driver);
    shift.press();
    run_one_scan_loop();
    letter.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_REPORT(driver, (KC_K, KC_U));
    EXPECT_REPORT(driver, (KC_U));
    shift.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    letter.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Same hand: Chordal Hold settles the mod-tap as a tap as soon as the other key
// is pressed, so a letter typed with the same hand keeps typing itself.
TEST_F(TapHoldIntegration, SameHandStaysATap) {
    TestDriver driver;
    InSequence s;

    KeymapKey shift(0, 1, 2, HB_K);
    KeymapKey letter(0, 2, 2, DE_H);
    set_keymap({shift, letter});

    EXPECT_NO_REPORT(driver);
    shift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_K));
    EXPECT_REPORT(driver, (KC_K, KC_H));
    letter.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_K));
    letter.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    shift.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Ctrl+Shift+V: both right-hand mod-taps and the target on the other hand.
// Permissive Hold settles the chord on the target's release, so the shortcut
// does not need the tapping term, and the target on the other hand is what
// makes it a chord at all.
TEST_F(TapHoldIntegration, CtrlShiftV) {
    TestDriver driver;
    InSequence s;

    KeymapKey ctrl(0, 0, 2, HB_J);
    KeymapKey shift(0, 1, 2, HB_K);
    KeymapKey v(0, 2, 0, DE_V);
    set_keymap({ctrl, shift, v});

    EXPECT_NO_REPORT(driver);
    ctrl.press();
    run_one_scan_loop();
    shift.press();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RCTL));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT, KC_V));
    EXPECT_REPORT(driver, (KC_RCTL, KC_RSFT));
    tap_key(v);
    VERIFY_AND_CLEAR(driver);

    EXPECT_REPORT(driver, (KC_RSFT));
    ctrl.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);

    EXPECT_EMPTY_REPORT(driver);
    shift.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// AltGr+a: HB_X sits on the exempt AltGr slot, so the same-hand chord is
// allowed, Permissive Hold settles the AltGr tap as held and the key override
// produces the umlaut.
TEST_F(TapHoldIntegration, AltGrChordKeepsAltGr) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey altgr(0, 5, 2, HB_X);
    KeymapKey a(0, 6, 2, HB_A);
    set_keymap({altgr, a});

    altgr.press();
    run_one_scan_loop();

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_QUOT)); // ä
    }
    tap_key(a);

    altgr.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Thumb exception: a layer-tap on the thumb row may form a chord with the key
// next to it even when that key is released first. The release does not force
// the thumb to a tap, so the layer engages at the tapping term and the buffered
// key is typed on it.
TEST_F(TapHoldIntegration, ThumbChordEngagesLayer) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey thumb(0, 0, 3, LT(_NUM, KC_SPC));
    KeymapKey key(0, 1, 3, DE_A);
    KeymapKey key_num(2, 1, 3, DE_1);
    set_keymap({thumb, key, key_num});

    thumb.press();
    run_one_scan_loop();
    key.press();
    run_one_scan_loop();
    key.release();
    run_one_scan_loop();

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_1));
    }
    idle_for(TAPPING_TERM);
    VERIFY_AND_CLEAR(driver);

    EXPECT_TRUE(layer_state_is(_NUM));

    thumb.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(_NUM));
    VERIFY_AND_CLEAR(driver);
}

// Thumbs are deliberately not permissive: a nested thumb-then-key sequence
// within the tapping term stays a Space tap, and the following key is typed on
// the base layer instead of the layer the thumb would have opened.
TEST_F(TapHoldIntegration, ThumbIsNotPermissive) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey space(0, 0, 3, LT(_NUM, KC_SPC));
    KeymapKey key(0, 1, 3, DE_A);
    KeymapKey key_num(2, 1, 3, DE_6);
    set_keymap({space, key, key_num});

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_A, KC_SPC));
        EXPECT_REPORT(driver, (KC_SPC));
    }
    space.press();
    run_one_scan_loop();
    key.press();
    run_one_scan_loop();
    key.release();
    run_one_scan_loop();
    space.release();
    run_one_scan_loop();

    EXPECT_FALSE(layer_state_is(_NUM));
    VERIFY_AND_CLEAR(driver);
}
