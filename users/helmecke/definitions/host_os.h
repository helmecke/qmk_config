#pragma once

#include QMK_KEYBOARD_H

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"

// Host OS settings that were actually applied, see helmecke.c. On the USB half
// a detected host whose settings are not applied yet is reported as OS_UNSURE;
// the peripheral half reports the OS synchronized over the split transport.
os_variant_t helmecke_os(void);
// True for the applied Apple targets, macOS and iOS alike.
bool helmecke_os_is_apple(void);
#endif // OS_DETECTION_ENABLE
