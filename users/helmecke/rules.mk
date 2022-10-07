CONSOLE_ENABLE = yes
TAP_DANCE_ENABLE = yes
MOUSEKEY_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
MOUSEKEY_ENABLE = yes  
UNICODE_ENABLE = yes
CUSTOM_LEADER_ENABLE = yes
CUSTOM_REPEAT_ENABLE = yes
CAPS_WORD_ENABLE = yes

CUSTOM_LEADER_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_LEADER_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_LEADER_ENABLE
	OPT_DEFS += -DCUSTOM_LEADER_TO_DL
	SRC += features/leader.c
	SRC += features/leaderfuncs.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dances.c
endif

ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += key_overrides.c
endif

ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
	SRC += caps_word.c
endif

CUSTOM_REPEAT_ENABLE ?= yes
ifeq ($(strip $(CUSTOM_REPEAT_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_REPEAT_ENABLE
	SRC += features/repeat.c
endif

SRC += helmecke.c
SRC += process_records.c
