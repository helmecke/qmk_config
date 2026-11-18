#!/usr/bin/env bash
# Stage this repository into an external qmk_firmware checkout so the Kyria
# keymap, the shared helmecke userspace and the fixtures under tests/ can be
# built with upstream tooling.
#
# Usage:
#   tests/stage-into-qmk.sh /path/to/qmk_firmware
#   QMK_FIRMWARE=/path/to/qmk_firmware tests/stage-into-qmk.sh
#
# The checkout is left untouched apart from these copied directories; nothing
# is symlinked and no QMK sources are modified.
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
qmk_root="${1:-${QMK_FIRMWARE:-}}"

if [[ -z "${qmk_root}" ]]; then
    echo "usage: $0 /path/to/qmk_firmware" >&2
    exit 2
fi

if [[ ! -d "${qmk_root}/quantum" || ! -d "${qmk_root}/keyboards" ]]; then
    echo "error: ${qmk_root} does not look like a qmk_firmware checkout" >&2
    exit 2
fi

copy_dir() {
    local src="$1"
    local dst="$2"
    rm -rf "${dst}"
    mkdir -p "$(dirname "${dst}")"
    cp -r "${src}" "${dst}"
}

copy_dir "${repo_root}/users/helmecke" "${qmk_root}/users/helmecke"
copy_dir "${repo_root}/keyboards/splitkb/kyria/keymaps/helmecke" "${qmk_root}/keyboards/splitkb/kyria/keymaps/helmecke"
copy_dir "${repo_root}/tests/helmecke_caps_word" "${qmk_root}/tests/helmecke_caps_word"
copy_dir "${repo_root}/tests/helmecke_os" "${qmk_root}/tests/helmecke_os"

cat <<EOF
Staged into ${qmk_root}

Build the firmware:
  make splitkb/kyria/rev2:helmecke CONVERT_TO=kb2040 -j2

Run the fixtures:
  make test:helmecke_caps_word
  make test:helmecke_os
EOF
