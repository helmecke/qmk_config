#pragma once

#include "test_common.h"

// Mirrors keyboards/splitkb/kyria/keymaps/helmecke/config.h for the settings
// this fixture exercises.
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 5000

// The shared userspace settings, including the preserved 200 ms tapping term.
#include "../../users/helmecke/config.h"
