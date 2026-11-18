#include QMK_KEYBOARD_H

#include "definitions/process_record.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#include "definitions/keymap_blocks.h"
#include "definitions/host_os.h"

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif // OS_DETECTION_ENABLE

#ifdef GERMAN_US_ENABLE
#    include "features/german_us.h"
#endif // GERMAN_US_ENABLE

#ifdef CAPS_WORD_ENABLE
#    include "features/caps_word_german.h"
#endif // CAPS_WORD_ENABLE

void matrix_scan_keymap(void);
