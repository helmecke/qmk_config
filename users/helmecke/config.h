#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 200

// Configure the global combo term (default: 50ms)
#define COMBO_TERM 60

// Mouse key speed and acceleration.
// Delay between pressing a movement key and cursor movement (default: 10)
#define MOUSEKEY_DELAY 5
// Time between cursor movements in milliseconds (default: 20)
#define MOUSEKEY_INTERVAL 13
// Maximum cursor speed at which acceleration stops (default: 10)
#define MOUSEKEY_MAX_SPEED 6
// Time until maximum cursor speed is reached (default: 30)
#define MOUSEKEY_TIME_TO_MAX 64
// Delay between pressing a wheel key and wheel movement (default: 10)
#define MOUSEKEY_WHEEL_DELAY 5
// Forces the keyboard to wait for a USB connection to be established before it starts up
// #define WAIT_FOR_USB
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
