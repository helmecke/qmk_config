# Copyright 2026 Jakob Helmecke
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# --------------------------------------------------------------------------------
# Keep this file, even if it is empty, as a marker that this folder contains tests
# --------------------------------------------------------------------------------

TAP_DANCE_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes
OS_DETECTION_ENABLE = yes
UNICODE_ENABLE = yes
MOUSEKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# The shared userspace lives in users/helmecke in the staged QMK checkout. Its
# dispatch chain and feature sources are compiled as they are on the keyboard.
OPT_DEFS += -DCUSTOM_LEADER_ENABLE
OPT_DEFS += -DGERMAN_US_ENABLE
# The test platform has no generated keyboard header.
OPT_DEFS += -DQMK_KEYBOARD_H=\"quantum.h\"

SRC += \
    users/helmecke/helmecke.c \
    users/helmecke/features/caps_word_german.c \
    users/helmecke/features/custom_leader.c \
    users/helmecke/features/custom_leader_func.c \
    users/helmecke/features/german_us.c \
    users/helmecke/features/key_override.c \
    users/helmecke/features/tap_dance.c

# The feature sources include the shared headers by name, as on the keyboard.
VPATH += users/helmecke
