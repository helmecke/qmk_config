#include QMK_KEYBOARD_H

#include "definitions/process_record.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#include "definitions/keymap_blocks.h"

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif // OS_DETECTION_ENABLE

#ifdef TAP_DANCE_ENABLE
#    include "features/tap_dance.h"
#endif // TAP_DANCE_ENABLE

#ifdef LEADER_ENABLE
#    include "features/leader.h"
#endif // LEADER_ENABLE

#ifdef CUSTOM_LEADER_ENABLE
#    include "features/custom_leader.h"
#endif // CUSTOM_LEADER_ENABLE

#ifdef SMART_CASE_ENABLE
#    include "features/smart_case.h"
#endif // SMART_CASE_ENABLE

#ifdef GERMAN_US_ENABLE
#    include "features/german_us.h"
#endif // GERMAN_US_ENABLE

void matrix_scan_keymap(void);
