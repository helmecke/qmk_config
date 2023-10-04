#pragma once

#include QMK_KEYBOARD_H

#include "../definitions/keycodes.h"
#include "../definitions/process_record.h"

process_record_result_t process_german_us(uint16_t keycode, keyrecord_t *record);
