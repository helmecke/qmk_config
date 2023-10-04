#pragma once

#include QMK_KEYBOARD_H

#include "../definitions/keycodes.h"
#include "../definitions/process_record.h"

typedef void *(*leader_func_t)(uint16_t);

// Check to see if we are leading
bool leader_sequence_active(void);
// Start leader sequence
void leader_start(void);
// Stop leader sequence
void leader_end(void);

// Process keycode for leader sequences
process_record_result_t process_leader(uint16_t keycode, const keyrecord_t *record);
