#pragma once

#include "test_common.h"

// Mirrors keyboards/splitkb/kyria/keymaps/helmecke/config.h: the detected host
// OS is applied from QMK's debounced callback and synchronized to the
// peripheral half.
#define SPLIT_DETECTED_OS_ENABLE
#define OS_DETECTION_DEBOUNCE 50

#include "../../users/helmecke/config.h"
