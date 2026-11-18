CONSOLE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
MOUSEKEY_ENABLE = yes
OS_DETECTION_ENABLE = yes

SRC += helmecke.c

ifeq ($(strip $(KEY_OVERRIDE_ENABLE)), yes)
	SRC += features/key_override.c
endif

KEYLOGGER_ENABLE ?= no
ifdef CONSOLE_ENABLE
    ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
        OPT_DEFS += -DKEYLOGGER_ENABLE
    endif
endif

GERMAN_US_ENABLE ?= yes
ifeq ($(strip $(GERMAN_US_ENABLE)), yes)
	OPT_DEFS += -DGERMAN_US_ENABLE
	SRC += features/german_us.c
endif

# Caps Word is enabled per keymap/keyboard. The German-aware policy callback is
# only compiled when the core feature is on, so other boards neither gain Caps
# Word nor depend on disabled core APIs.
ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
	SRC += features/caps_word_german.c
endif
