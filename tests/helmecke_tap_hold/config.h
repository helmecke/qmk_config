#pragma once

#include "test_common.h"

// Mirrors keyboards/splitkb/kyria/keymaps/helmecke/config.h for the tap-hold
// settings this fixture exercises: Chordal Hold on the handedness rule and
// Permissive Hold only for the home-row mod-taps.
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD_PER_KEY

// The shared userspace settings, including the preserved 200 ms tapping term.
#include "../../users/helmecke/config.h"
