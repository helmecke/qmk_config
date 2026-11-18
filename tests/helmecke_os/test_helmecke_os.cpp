// Copyright 2026 Jakob Helmecke
// SPDX-License-Identifier: GPL-2.0-or-later

// Debounced host OS application: the applied OS drives modifier swapping,
// Unicode input mode and Apple-specific punctuation, and is only updated from
// QMK's debounced detected-OS callback.

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

extern "C" {
#include "os_detection.h"
#include "unicode/unicode.h"
#include "usb_device_state.h"

bool         helmecke_os_is_apple(void);
os_variant_t helmecke_os(void);
}

// Console logging must not be required for OS application.
#ifdef CONSOLE_ENABLE
#    error "the helmecke_os fixture must be built without CONSOLE_ENABLE"
#endif

using ::testing::_;
using ::testing::AnyNumber;

namespace {

// Collected USB wLength fingerprints, see quantum/os_detection/tests.
const std::initializer_list<uint16_t> windows_setup = {0xFF, 0xFF, 0x4};
const std::initializer_list<uint16_t> linux_setup   = {0xFF, 0xFF, 0xFF};
const std::initializer_list<uint16_t> macos_setup   = {0x2, 0x24, 0x2, 0x28, 0xFF};
const std::initializer_list<uint16_t> ios_setup     = {0x2, 0x24, 0x2, 0x28};
const std::initializer_list<uint16_t> unknown_setup = {0x1, 0x3};

class HelmeckeOs : public TestFixture {
   public:
    // A keyboard reset clears the detection state and a fresh host starts
    // enumerating. QMK keeps detection state over a USB reconnect at this
    // revision, so the reset is what models switching to another host.
    void connectAndFeed(std::initializer_list<uint16_t> w_lengths) {
        erase_wlength_data();
        struct usb_device_state state = {};
        state.configure_state         = USB_DEVICE_STATE_CONFIGURED;
        os_detection_notify_usb_device_state_change(state);
        for (uint16_t w_length : w_lengths) {
            process_wlength(w_length);
        }
    }

    void settle() {
        idle_for(OS_DETECTION_DEBOUNCE + 1);
    }
};

} // namespace

TEST_F(HelmeckeOs, AppliesWindows) {
    // The test driver must outlive the scan loops: keyboard_task() polls the
    // host LED state through the driver.
    TestDriver driver;

    connectAndFeed(windows_setup);
    settle();

    EXPECT_EQ(helmecke_os(), OS_WINDOWS);
    EXPECT_FALSE(helmecke_os_is_apple());
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_FALSE(keymap_config.swap_rctl_rgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_WINCOMPOSE);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(HelmeckeOs, AppliesLinux) {
    TestDriver driver;

    connectAndFeed(linux_setup);
    settle();

    EXPECT_EQ(helmecke_os(), OS_LINUX);
    EXPECT_FALSE(helmecke_os_is_apple());
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_LINUX);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(HelmeckeOs, AppliesMacosAndIosAsApple) {
    TestDriver driver;

    connectAndFeed(macos_setup);
    settle();

    EXPECT_EQ(helmecke_os(), OS_MACOS);
    EXPECT_TRUE(helmecke_os_is_apple());
    EXPECT_TRUE(keymap_config.swap_lctl_lgui);
    EXPECT_TRUE(keymap_config.swap_rctl_rgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_MACOS);

    connectAndFeed(ios_setup);
    settle();

    EXPECT_EQ(helmecke_os(), OS_IOS);
    EXPECT_TRUE(helmecke_os_is_apple());
    EXPECT_TRUE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_MACOS);

    VERIFY_AND_CLEAR(driver);
}

// An unknown host keeps safe non-Apple behavior and normal typing instead of
// claiming a successful Windows detection.
TEST_F(HelmeckeOs, UnknownHostKeepsSafeDefaults) {
    TestDriver driver;

    connectAndFeed(macos_setup);
    settle();
    ASSERT_EQ(helmecke_os(), OS_MACOS);

    connectAndFeed(unknown_setup);
    settle();

    EXPECT_EQ(helmecke_os(), OS_UNSURE);
    EXPECT_FALSE(helmecke_os_is_apple());
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_WINCOMPOSE);

    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(AnyNumber());
    KeymapKey a(0, 0, 0, KC_A);
    set_keymap({a});
    tap_key(a);
    VERIFY_AND_CLEAR(driver);
}

// The OS is applied only after QMK's debounce window, and a changed host is
// applied on the next debounced report.
TEST_F(HelmeckeOs, AppliesAfterDebounceAndFollowsHostChanges) {
    TestDriver driver;

    connectAndFeed(macos_setup);
    settle();
    ASSERT_EQ(helmecke_os(), OS_MACOS);

    connectAndFeed(linux_setup);
    idle_for(OS_DETECTION_DEBOUNCE - 10);
    EXPECT_EQ(helmecke_os(), OS_MACOS);
    EXPECT_TRUE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_MACOS);

    idle_for(20);
    EXPECT_EQ(helmecke_os(), OS_LINUX);
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_LINUX);

    connectAndFeed(windows_setup);
    settle();
    EXPECT_EQ(helmecke_os(), OS_WINDOWS);
    EXPECT_FALSE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_WINCOMPOSE);

    connectAndFeed(macos_setup);
    settle();
    EXPECT_EQ(helmecke_os(), OS_MACOS);
    EXPECT_TRUE(keymap_config.swap_lctl_lgui);
    EXPECT_EQ(get_unicode_input_mode(), UNICODE_MODE_MACOS);

    VERIFY_AND_CLEAR(driver);
}
