CONSOLE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
LEADER_ENABLE = no
MOUSEKEY_ENABLE = yes
OS_DETECTION_DEBUG_ENABLE = yes
OS_DETECTION_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODE_ENABLE = yes

SRC += helmecke.c
SRC += definitions/keycodes.c

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
	SRC += features/os_toggle.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += features/tap_dance.c
endif

ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += features/key_override.c
endif

CUSTOM_LEADER_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_LEADER_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_LEADER_ENABLE
	SRC += features/custom_leader.c
	SRC += features/custom_leader_func.c
endif

KEYLOGGER_ENABLE ?= no
ifdef CONSOLE_ENABLE
    ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
        OPT_DEFS += -DKEYLOGGER_ENABLE
    endif
endif

SMART_CASE_ENABLE ?= yes
ifeq ($(strip $(SMART_CASE_ENABLE)), yes)
	OPT_DEFS += -DSMART_CASE_ENABLE
	SRC += features/smart_case.c
endif

GERMAN_US_ENABLE ?= yes
ifeq ($(strip $(GERMAN_US_ENABLE)), yes)
	OPT_DEFS += -DGERMAN_US_ENABLE
	SRC += features/german_us.c
endif
