// Copyright 2026 Jakob Helmecke
// SPDX-License-Identifier: GPL-2.0-or-later

// German-aware Caps Word integration, exercised through QMK's real event
// processing: the shared userspace dispatcher, tap dance, key overrides and
// Caps Word are all compiled from their normal sources.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
#include "../../users/helmecke/definitions/keycodes.h"
#include "../../users/helmecke/definitions/layers.h"

bool leader_sequence_active(void);
void leader_end(void);
}

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::InSequence;

namespace {

// Reports without a key, e.g. a modifier being registered or a key release, are
// interleaved with the key reports the individual tests assert on: reports are
// sent for weak modifier changes, for key releases and when a key override
// suppresses a key.
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

class CapsWordIntegration : public TestFixture {
   public:
    void tapKey(KeymapKey &key) {
        key.press();
        run_one_scan_loop();
        key.release();
        run_one_scan_loop();
    }

    void holdKey(KeymapKey &key) {
        key.press();
        idle_for(TAPPING_TERM);
        run_one_scan_loop();
    }

    // Presses both Shift keys, holds the first one past the tapping term when
    // it is a mod-tap, then releases both in the opposite order.
    void pressBothShifts(KeymapKey &left, KeymapKey &right, bool right_first) {
        KeymapKey &first  = right_first ? right : left;
        KeymapKey &second = right_first ? left : right;
        first.press();
        run_one_scan_loop();
        second.press();
        if (IS_QK_MOD_TAP(first.code)) {
            idle_for(TAPPING_TERM);
        }
        run_one_scan_loop();
        first.release();
        run_one_scan_loop();
        second.release();
        run_one_scan_loop();
    }
};

} // namespace

// Both-Shifts activation works with the D/K home-row Shift mod-taps as well as
// with explicit left and right Shift keys. Plain and mod-tap Shift pairs
// activate in either press/release order; one-shot shifts follow QMK's tested
// order (left first), because a one-shot mod is consumed by the next key press.
TEST_F(CapsWordIntegration, BothShiftsTurnOnCapsWord) {
    struct ShiftPair {
        const char *name;
        uint16_t    left;
        uint16_t    right;
        bool        both_orders;
    };
    const ShiftPair pairs[] = {
        {"plain shifts", KC_LSFT, KC_RSFT, true},
        {"one-shot shifts", OSM(MOD_LSFT), OSM(MOD_RSFT), false},
        {"D and K mod-taps", HB_D, HB_K, true},
    };

    for (const auto &pair : pairs) {
        for (bool right_first : {false, true}) {
            if (right_first && !pair.both_orders) {
                continue;
            }
            SCOPED_TRACE(std::string(pair.name) + (right_first ? ", right first" : ", left first"));
            TestDriver driver;
            allow_modifier_reports(driver);

            KeymapKey left(0, 0, 0, pair.left);
            KeymapKey right(0, 1, 0, pair.right);
            set_keymap({left, right});

            // Each order starts from a clean modifier state; one-shot state in
            // particular survives caps_word_off(), and a quick repeat of the
            // same matrix position would count as a tap of the previous one.
            clear_mods();
            clear_oneshot_mods();
            clear_oneshot_locked_mods();
            caps_word_off();
            idle_for(TAPPING_TERM + 1);
            EXPECT_FALSE(is_caps_word_on());

            pressBothShifts(left, right, right_first);
            EXPECT_TRUE(is_caps_word_on());

            caps_word_off();
            VERIFY_AND_CLEAR(driver);
        }
    }
}

// Ordinary D/K taps keep typing letters, and an individual hold still acts as
// Shift without turning Caps Word on.
TEST_F(CapsWordIntegration, HomeRowShiftTapsAndHolds) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey d(0, 0, 0, HB_D);
    KeymapKey k(0, 1, 0, HB_K);
    KeymapKey c(0, 2, 0, KC_C);
    set_keymap({d, k, c});

    caps_word_off();

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_D));
    }
    tapKey(d);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_K));
    }
    tapKey(k);

    // Holding one home-row Shift and typing a key is an ordinary shortcut.
    holdKey(d);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_C));
    }
    tapKey(c);
    d.release();
    run_one_scan_loop();

    EXPECT_FALSE(is_caps_word_on());
    VERIFY_AND_CLEAR(driver);
}

// Letters are shifted, the German minus key becomes underscore and digits stay
// unchanged: hello-world123 -> HELLO_WORLD123.
TEST_F(CapsWordIntegration, GermanMinusAndDigits) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey h(0, 0, 0, DE_H);
    KeymapKey e(0, 1, 0, DE_E);
    KeymapKey l1(0, 2, 0, DE_L);
    KeymapKey l2(0, 3, 0, DE_L);
    KeymapKey o1(0, 4, 0, DE_O);
    KeymapKey mins(0, 5, 0, DE_MINS);
    KeymapKey w(0, 6, 0, DE_W);
    KeymapKey o2(0, 7, 0, DE_O);
    KeymapKey r(0, 8, 0, DE_R);
    KeymapKey l3(0, 9, 0, DE_L);
    KeymapKey d(0, 0, 1, DE_D);
    KeymapKey one(0, 1, 1, DE_1);
    KeymapKey two(0, 2, 1, DE_2);
    KeymapKey three(0, 3, 1, DE_3);
    KeymapKey unds(0, 4, 1, DE_UNDS);
    set_keymap({h, e, l1, l2, o1, mins, w, o2, r, l3, d, one, two, three, unds});

    caps_word_on();

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_H));
        EXPECT_REPORT(driver, (KC_LSFT, KC_E));
        EXPECT_REPORT(driver, (KC_LSFT, KC_L));
        EXPECT_REPORT(driver, (KC_LSFT, KC_L));
        EXPECT_REPORT(driver, (KC_LSFT, KC_O));
        EXPECT_REPORT(driver, (KC_LSFT, KC_SLSH)); // German minus, typed as underscore
        EXPECT_REPORT(driver, (KC_LSFT, KC_W));
        EXPECT_REPORT(driver, (KC_LSFT, KC_O));
        EXPECT_REPORT(driver, (KC_LSFT, KC_R));
        EXPECT_REPORT(driver, (KC_LSFT, KC_L));
        EXPECT_REPORT(driver, (KC_LSFT, KC_D));
        EXPECT_REPORT(driver, (KC_1));
        EXPECT_REPORT(driver, (KC_2));
        EXPECT_REPORT(driver, (KC_3));
    }
    tapKey(h);
    tapKey(e);
    tapKey(l1);
    tapKey(l2);
    tapKey(o1);
    tapKey(mins);
    tapKey(w);
    tapKey(o2);
    tapKey(r);
    tapKey(l3);
    tapKey(d);
    tapKey(one);
    tapKey(two);
    tapKey(three);

    // The underscore key on the symbol layer continues the word unshifted.
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_SLSH));
    }
    tapKey(unds);

    EXPECT_TRUE(is_caps_word_on());
    VERIFY_AND_CLEAR(driver);
}

// AltGr umlauts produce Ä/Ö/Ü, AltGr+S produces two S keystrokes, and the mode
// continues. No AltGr or stale Shift leaks into the synthetic output.
TEST_F(CapsWordIntegration, AltGrUmlautsAndSharpS) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey altgr(0, 0, 0, HB_X);
    KeymapKey a(0, 1, 0, HB_A);
    KeymapKey u(0, 2, 0, DE_U);
    KeymapKey o(0, 3, 0, DE_O);
    KeymapKey s(0, 4, 0, HB_S);
    KeymapKey n(0, 5, 0, DE_N);
    KeymapKey bspc(0, 6, 0, LT(_SYM, KC_BSPC));
    set_keymap({altgr, a, u, o, s, n, bspc});

    caps_word_on();
    holdKey(altgr);

    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_LSFT, KC_QUOT)); // Ä
    }
    tapKey(a);
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_LSFT, KC_LBRC)); // Ü
    }
    tapKey(u);
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_LSFT, KC_SCLN)); // Ö
    }
    tapKey(o);
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_LSFT, KC_S)); // SS
        EXPECT_REPORT(driver, (KC_LSFT, KC_S));
    }
    tapKey(s);

    altgr.release();
    run_one_scan_loop();

    // SS is two emitted characters, so Backspace removes one S at a time and
    // continues the word.
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_BSPC));
    }
    tapKey(bspc);
    EXPECT_TRUE(is_caps_word_on());

    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_LSFT, KC_N));
    }
    tapKey(n);

    EXPECT_TRUE(is_caps_word_on());
    VERIFY_AND_CLEAR(driver);
}

// AltGr+dot (!) and AltGr+comma (?) both end Caps Word before they emit.
TEST_F(CapsWordIntegration, AltGrPunctuationEndsCapsWord) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey altgr(0, 0, 0, HB_X);
    KeymapKey dot(0, 1, 0, HB_DOT);
    KeymapKey comma(0, 2, 0, TD_COMM);
    set_keymap({altgr, dot, comma});

    // Caps Word first, then AltGr: activating Caps Word clears held modifiers,
    // so a held AltGr has to be established afterwards, as when typing.
    caps_word_on();
    holdKey(altgr);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_1)); // !
    }
    tapKey(dot);
    EXPECT_FALSE(is_caps_word_on());
    altgr.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM + 1);

    caps_word_on();
    holdKey(altgr);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_MINS)); // ?
    }
    tapKey(comma);
    EXPECT_FALSE(is_caps_word_on());

    altgr.release();
    run_one_scan_loop();
    VERIFY_AND_CLEAR(driver);
}

// Outside Caps Word the AltGr paths keep their old output and held-modifier
// semantics: ä and ß unshifted, no word state involved.
TEST_F(CapsWordIntegration, AltGrOutsideCapsWord) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey altgr(0, 0, 0, HB_X);
    KeymapKey a(0, 1, 0, HB_A);
    KeymapKey s(0, 2, 0, HB_S);
    set_keymap({altgr, a, s});

    caps_word_off();
    holdKey(altgr);
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_QUOT)); // ä
    }
    tapKey(a);
    {
        InSequence s1;
        EXPECT_REPORT(driver, (KC_MINS)); // ß
    }
    tapKey(s);
    altgr.release();
    run_one_scan_loop();

    EXPECT_FALSE(is_caps_word_on());
    VERIFY_AND_CLEAR(driver);
}

// The four outer corner keys type the dedicated German umlauts and ß; the ß key
// types SS while Caps Word is active and keeps the word going.
TEST_F(CapsWordIntegration, DedicatedUmlautKeys) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey adia(0, 0, 0, DE_ADIA);
    KeymapKey udia(0, 1, 0, DE_UDIA);
    KeymapKey odia(0, 2, 0, DE_ODIA);
    KeymapKey sz(0, 3, 0, U_SZ);
    set_keymap({adia, udia, odia, sz});

    // Outside Caps Word: lowercase umlauts and ß.
    caps_word_off();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_QUOT));
    }
    tapKey(adia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LBRC));
    }
    tapKey(udia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_SCLN));
    }
    tapKey(odia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_MINS));
    }
    tapKey(sz);

    // Inside Caps Word: Ä/Ö/Ü and SS; the word continues.
    caps_word_on();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_QUOT));
    }
    tapKey(adia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_LBRC));
    }
    tapKey(udia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_SCLN));
    }
    tapKey(odia);
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_S));
        EXPECT_REPORT(driver, (KC_LSFT, KC_S));
    }
    tapKey(sz);
    EXPECT_TRUE(is_caps_word_on());

    VERIFY_AND_CLEAR(driver);
}

// Ordinary comma taps end the word and keep the comma; a double tap starts the
// custom leader instead.
TEST_F(CapsWordIntegration, CommaAndLeader) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey comma(0, 0, 0, TD_COMM);
    set_keymap({comma});

    caps_word_on();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_COMM));
    }
    tapKey(comma);
    idle_for(TAPPING_TERM + 1);
    EXPECT_FALSE(is_caps_word_on());

    caps_word_on();
    comma.press();
    run_one_scan_loop();
    comma.release();
    run_one_scan_loop();
    comma.press();
    run_one_scan_loop();
    comma.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM + 1);
    EXPECT_TRUE(leader_sequence_active());
    EXPECT_FALSE(is_caps_word_on());

    leader_end();
    VERIFY_AND_CLEAR(driver);
}

// Consumed punctuation ends the word before it emits, without inheriting Caps
// Word's Shift, and the next key is not shifted.
TEST_F(CapsWordIntegration, ConsumedPunctuationEndsCapsWord) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey plus(0, 0, 0, U_PLUS);
    KeymapKey slash(0, 1, 0, U_SLSH);
    KeymapKey a(0, 2, 0, KC_A);
    set_keymap({plus, slash, a});

    caps_word_on();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_RBRC)); // German "+" unshifted
    }
    tapKey(plus);
    EXPECT_FALSE(is_caps_word_on());

    caps_word_on();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_7)); // German "/", the key's own shift only
    }
    tapKey(slash);
    EXPECT_FALSE(is_caps_word_on());

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_A));
    }
    tapKey(a);

    VERIFY_AND_CLEAR(driver);
}

// Space and Shift end the word; Backspace keeps editing it.
TEST_F(CapsWordIntegration, SpaceShiftAndBackspace) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey space(0, 0, 0, LT(_NUM, KC_SPC));
    KeymapKey backspace(0, 1, 0, LT(_SYM, KC_BSPC));
    KeymapKey sft(0, 2, 0, KC_LSFT);
    KeymapKey a(0, 3, 0, DE_A);
    set_keymap({space, backspace, sft, a});

    // Backspace continues the word and stays unshifted.
    caps_word_on();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_BSPC));
    }
    tapKey(backspace);
    EXPECT_TRUE(is_caps_word_on());

    // Space ends the word.
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_SPC));
    }
    tapKey(space);
    EXPECT_FALSE(is_caps_word_on());

    // Shift ends the word.
    caps_word_on();
    tapKey(sft);
    EXPECT_FALSE(is_caps_word_on());

    // Nothing is stuck afterwards.
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_A));
    }
    tapKey(a);

    VERIFY_AND_CLEAR(driver);
}

// Momentary layer access stays usable while Caps Word is active.
TEST_F(CapsWordIntegration, MomentaryLayerAccess) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey layerBspc(0, 0, 0, LT(_SYM, KC_BSPC));
    KeymapKey a(0, 1, 0, DE_A);
    set_keymap({layerBspc, a});

    caps_word_on();
    holdKey(layerBspc);
    EXPECT_TRUE(layer_state_is(_SYM));
    EXPECT_TRUE(is_caps_word_on());
    layerBspc.release();
    run_one_scan_loop();
    EXPECT_FALSE(layer_state_is(_SYM));
    EXPECT_TRUE(is_caps_word_on());

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_A));
    }
    tapKey(a);
    EXPECT_TRUE(is_caps_word_on());

    VERIFY_AND_CLEAR(driver);
}

// A Ctrl shortcut ends the word and leaves no modifiers or Shift behind.
TEST_F(CapsWordIntegration, ShortcutEndsCapsWord) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey ctl(0, 0, 0, KC_LCTL);
    KeymapKey c(0, 1, 0, KC_C);
    KeymapKey a(0, 2, 0, DE_A);
    set_keymap({ctl, c, a});

    caps_word_on();
    ctl.press();
    run_one_scan_loop();
    EXPECT_FALSE(is_caps_word_on());
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LCTL, KC_C));
    }
    c.press();
    run_one_scan_loop();
    c.release();
    run_one_scan_loop();
    ctl.release();
    run_one_scan_loop();

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_A));
    }
    tapKey(a);

    VERIFY_AND_CLEAR(driver);
}

// The repaired quote/GUI mod-tap taps its punctuation instead of a truncated
// placeholder key, and still holds GUI for shortcuts.
TEST_F(CapsWordIntegration, QuoteGuiModTap) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey quot(0, 0, 0, HB_QUOT);
    KeymapKey sft(0, 1, 0, KC_LSFT);
    KeymapKey c(0, 2, 0, KC_C);
    set_keymap({quot, sft, c});

    // Tap: single quote (Shift + the German '#' key).
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_NUHS));
    }
    tapKey(quot);

    // Shift + tap: double quote (Shift + the German '2' key).
    sft.press();
    run_one_scan_loop();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_2));
    }
    tapKey(quot);
    sft.release();
    run_one_scan_loop();

    // Let the mod-tap quick-tap window expire, otherwise the next press would
    // count as a repeat tap of the same key instead of a hold.
    idle_for(TAPPING_TERM + 1);

    // Hold: GUI acts as a shortcut modifier.
    quot.press();
    idle_for(TAPPING_TERM);
    run_one_scan_loop();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_RGUI, KC_C));
    }
    c.press();
    run_one_scan_loop();
    c.release();
    run_one_scan_loop();
    quot.release();
    run_one_scan_loop();

    VERIFY_AND_CLEAR(driver);
}

// A held comma sends End and a comma, still outside Caps Word.
TEST_F(CapsWordIntegration, CommaHoldDance) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey comma(0, 0, 0, TD_COMM);
    set_keymap({comma});

    caps_word_on();
    comma.press();
    run_one_scan_loop();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_END));
        EXPECT_REPORT(driver, (KC_COMM));
    }
    idle_for(TAPPING_TERM + 1);
    comma.release();
    run_one_scan_loop();
    EXPECT_FALSE(is_caps_word_on());

    VERIFY_AND_CLEAR(driver);
}

// An interrupted comma tap still emits the comma and leaves no stuck state.
TEST_F(CapsWordIntegration, CommaInterruptedTap) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey comma(0, 0, 0, TD_COMM);
    KeymapKey a(0, 1, 0, KC_A);
    set_keymap({comma, a});

    caps_word_on();
    comma.press();
    run_one_scan_loop();
    EXPECT_FALSE(is_caps_word_on());

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_COMM));
        EXPECT_REPORT(driver, (KC_A));
    }
    a.press();
    run_one_scan_loop();
    a.release();
    run_one_scan_loop();
    comma.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM + 1);

    VERIFY_AND_CLEAR(driver);
}

// The leader W action still works outside capitalization handling.
TEST_F(CapsWordIntegration, LeaderWAction) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey comma(0, 0, 0, TD_COMM);
    KeymapKey w(0, 1, 0, DE_W);
    set_keymap({comma, w});

    caps_word_off();
    comma.press();
    run_one_scan_loop();
    comma.release();
    run_one_scan_loop();
    comma.press();
    run_one_scan_loop();
    comma.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM + 1);
    ASSERT_TRUE(leader_sequence_active());

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_SLSH)); // German minus, the leader W action
    }
    tapKey(w);
    EXPECT_FALSE(leader_sequence_active());

    VERIFY_AND_CLEAR(driver);
}

// A tap interrupted by another key still types the quote, and no placeholder
// key leaks from the mod-tap tap field.
TEST_F(CapsWordIntegration, QuoteInterruptedTap) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey quot(0, 0, 0, HB_QUOT);
    KeymapKey c(0, 1, 0, KC_C);
    set_keymap({quot, c});

    quot.press();
    run_one_scan_loop();
    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_NUHS));
        EXPECT_REPORT(driver, (KC_C));
    }
    c.press();
    run_one_scan_loop();
    c.release();
    run_one_scan_loop();
    quot.release();
    run_one_scan_loop();
    idle_for(TAPPING_TERM + 1);

    VERIFY_AND_CLEAR(driver);
}

// Caps Word ends after the configured idle timeout and does not come back.
TEST_F(CapsWordIntegration, IdleTimeout) {
    TestDriver driver;
    allow_modifier_reports(driver);

    KeymapKey a(0, 0, 0, DE_A);
    set_keymap({a});

    caps_word_on();
    run_one_scan_loop();
    idle_for(CAPS_WORD_IDLE_TIMEOUT - 100);
    EXPECT_TRUE(is_caps_word_on());
    idle_for(200);
    EXPECT_FALSE(is_caps_word_on());

    {
        InSequence s;
        EXPECT_REPORT(driver, (KC_A));
    }
    tapKey(a);

    VERIFY_AND_CLEAR(driver);
}
